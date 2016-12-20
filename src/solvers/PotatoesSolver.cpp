//
// Created by julien on 12/10/16.
//

#include <iostream>
#include "PotatoesSolver.h"
#include <algorithm>

using namespace std;

PotatoesSolver::PotatoesSolver(const std::string &input_path, const std::string &output_path) : Solver(input_path,
                                                                                                       output_path) {

}

void PotatoesSolver::solve() {
    int nb_color, nb_number;

    //Read the cards from input file
    cards = card_reader->readCards(input_path, nb_color, nb_number);

    //Create the graph from the cards
    builder->setup(nb_color,nb_number);
    builder->read_cards(cards);
    graph = builder->build_graph();

    //Compute potatoes
    list<list<Node*>*>* potatoes;
    potatoes = graph->potatoesDFS();
    graph->unMarkNodes();
    //Adding an empty potato at the end of the list
    potatoes->push_back(new list<Node*>());

    //Output the result
  //  DrawingBuilderPotatoes* drawingBuilderPotatoes = new DrawingBuilderPotatoes();
  //  drawingBuilderPotatoes -> readPotatoes(potatoes,nb_color,nb_number);
  //  drawingBuilderPotatoes -> outputPotatoes(output_path);

    //Generate all paths for a potatoes
    longest_path(potatoes);
}

PotatoesSolver::~PotatoesSolver() {
    delete graph;
    delete drawingBuilderPotatoes;
    std::vector<Card *>::iterator it;
    for (it = cards->begin();it != cards->end(); ++it)
        delete *it;
    delete cards;
}

PotatoesSolver::PotatoesSolver() : Solver(){
    card_reader = new CardReader();
    builder = new GraphBuilder();
}

list<Node *> *PotatoesSolver::longest_path(list<list<Node *> *> *potatoes) {
    cout << "nombre de patates : " << potatoes->size() << endl << flush;
    if (potatoes->empty())
        return 0;

    std::list<Signature*>* signatures_previous = new std::list<Signature*>();
    list<Node*>* intersection_previous = new list<Node*>();
    list<Node *>* current_potato;
    list<list<Node *> *>::iterator potatoes_it = potatoes->begin();

    while(potatoes_it != potatoes->end()){

 //       cout << "next potato" << endl<<flush;
        current_potato = *potatoes_it;

        cout << "current potato size : " << current_potato->size() << endl << flush;
        potatoes_it++;

        if (potatoes_it == potatoes->end())
            break;

        list<Node *>* next_potato = *potatoes_it;

        cout << endl;
        list<Node*>* intersection_next = intersect_potatoes(current_potato, next_potato);

//        cout << "intersection size : " << intersection_next->size() << endl;
        /*cout << "previous :" <<endl;
        list<Node*>::iterator intersection_previous_it = intersection_previous->begin();
        for (;intersection_previous_it != intersection_previous->end(); intersection_previous_it++)
            cout << (*intersection_previous_it)->toString() << " ";
        cout << endl;*/

//        cout << "intersection size : " << intersection_next->size() << endl;
        /*cout << "next :" <<endl;
        list<Node*>::iterator intersection_next_it = intersection_next->begin();
        for (;intersection_next_it != intersection_next->end(); intersection_next_it++)
            cout << (*intersection_next_it)->toString() << " ";
        cout << endl;*/

        list<list<PathComponent *> *>* paths = allPaths(current_potato, intersection_previous,intersection_next);

        std::list<Signature*>* signatures_current  = paths_to_Signatures(paths);
//        cout << "signature size : " << signatures_current->size() << endl;

        mergeSignatures(signatures_current, signatures_previous);

       // signatures_previous = signatures_current;
        signatures_previous->insert(signatures_previous->end(), signatures_current->begin(), signatures_current->end());

        intersection_previous = intersection_next;
    }

    list<Signature*>::iterator signature_it = signatures_previous->begin();
    for (;signature_it != signatures_previous->end(); signature_it++)
        cout << (*signature_it)->toString() << endl;
    return 0;
}

void PotatoesSolver::mergeSignatures(list<Signature*>* signatures_current, list<Signature*>* signatures_past){
    list<Signature*>::iterator signature_it;
    list<Signature*>::iterator signatures_past_it;

    for (signature_it = signatures_current->begin(); signature_it != signatures_current->end(); signature_it ++){
        Signature* past_version = (*signature_it)->createPastVesion();
        for (signatures_past_it = signatures_past->begin(); signatures_past_it != signatures_past->end(); signatures_past_it++){
         //   cout << "merge past : " << past_version->toString() << endl << "with : " << (*signature_it)->toString() << endl ;

            if ((*signatures_past_it)->match(past_version)){
                cout << "merge past : " << past_version->toString() << endl << "with : " << (*signature_it)->toString() << endl ;
                signatures_current->push_back((*signature_it)->merge(past_version));
            }
        }
        delete past_version;
    }
}

/*
 * Retourne l'intersection de deux patates
 */
list<Node*>* PotatoesSolver::intersect_potatoes(list<Node *> *current_potatoe, list<Node *> *next_potatoe) {
    list<Node*>::iterator current_it;
    list<Node*>::iterator next_it;
    list<Node*>* intersection = new list<Node*>();

    for(current_it  = current_potatoe->begin();current_it != current_potatoe->end(); current_it++){
        for(next_it = next_potatoe->begin();next_it != next_potatoe->end(); next_it++){
            if (*current_it == *next_it){
                intersection->push_back(*current_it);
            }
        }
    }
    return intersection;
}

/*
 * Used for recursion
 * Prend un chemin, et crée tous les chemins qui le continuent
 * possibilité de fuite memoire
 */
void search_paths(list<PathComponent*>* path, list<list<PathComponent*>*>* all_paths,
                                          list<Node*>* intersection_previous ,list<Node*>* intersection_next,
                                          list<Node *> *potatoe) {
    Node *current = path->back()->getNode();
    //leave if already in the path
    if (current->isMarked())
        return;

    //leave if not the potato
    if (std::find(potatoe->begin(), potatoe->end(), current) == potatoe->end()){
        return;
    }
    current->setMarked(true);


    //Adding elemements of intersection in neighborhood of nodes in the intersection previous
    set<Node *> *neighbors = current->getNeighbors();


    if (std::find(intersection_previous->begin(), intersection_previous->end(), current) != intersection_previous->end()) {
        list<Node *>::iterator intersection_previous_it;

        for (intersection_previous_it = intersection_previous->begin();
             intersection_previous_it != intersection_previous->end(); intersection_previous_it++) {
            if (*intersection_previous_it != current)
                neighbors->insert(*intersection_previous_it);
        }
    }

    //Adding elemements of intersection in neighborhood of nodes in the intersection next
    if (std::find(intersection_next->begin(), intersection_next->end(), current) != intersection_next->end()) {
        list<Node *>::iterator intersection_next_it;

        for (intersection_next_it = intersection_next->begin();
             intersection_next_it != intersection_next->end(); intersection_next_it++) {
            if (*intersection_next_it != current)
                neighbors->insert(*intersection_next_it);
        }
    }

    if (neighbors->empty()) {
        //we finished this path, unmark the node
        return;
    }

    set<Node *>::iterator neighbors_it;

    for (neighbors_it = neighbors->begin(); neighbors_it != neighbors->end(); neighbors_it++) {
        //Si on a déjà vu ce voisin, on passe
        if ((*neighbors_it)->isMarked())
            continue;

        if (std::find(intersection_previous->begin(), intersection_previous->end(), current) !=
            intersection_previous->end()) {
            list<PathComponent *> *new_path = new std::list<PathComponent *>();

            new_path->resize(path->size());
            copy(path->begin(), path->end(), new_path->begin());
            new_path->push_back(new PathComponent((*neighbors_it), '*'));
            all_paths->push_back(new_path);
            search_paths(new_path, all_paths,
                         intersection_previous, intersection_next, potatoe);
        //    (*neighbors_it)->setMarked(false);
        }
        if (std::find(intersection_next->begin(), intersection_next->end(), current) != intersection_next->end()) {
            list<PathComponent *> *new_path = new std::list<PathComponent *>();

            new_path->resize(path->size());
            copy(path->begin(), path->end(), new_path->begin());
            new_path->push_back(new PathComponent((*neighbors_it), '+'));
            all_paths->push_back(new_path);

            search_paths(new_path, all_paths,
                         intersection_previous, intersection_next, potatoe);
        //    (*neighbors_it)->setMarked(false);
        }
        list<PathComponent *> *new_path = new std::list<PathComponent *>();

        new_path->resize(path->size());
        copy(path->begin(), path->end(), new_path->begin());
        new_path->push_back(new PathComponent((*neighbors_it), '-'));
        all_paths->push_back(new_path);

        search_paths(new_path, all_paths,
                     intersection_previous, intersection_next, potatoe);
    //    (*neighbors_it)->setMarked(false);

    }
    //we finished this path, unmark the node
    current->setMarked(false);
}

/*
 * return all paths using recursion
 * we must use the previous intersection to define the "*" paths
 * and next intersection to define "+" paths
 */
    list<list<PathComponent *> *> *PotatoesSolver::allPaths(list<Node *> *potato, list<Node *> *intersection_previous,
                                                            list<Node *> *intersection_next) {
        list<list<PathComponent *> *> *all_paths = new list<list<PathComponent *> *>();
        list<Node *>::iterator potato_it;

        for (potato_it = potato->begin(); potato_it != potato->end(); potato_it++) {
            list<PathComponent *> *start_path_comp = new list<PathComponent *>();
            start_path_comp->push_back(new PathComponent(*potato_it, '-'));
            search_paths(start_path_comp, all_paths, intersection_previous,
                         intersection_next,
                         potato);

            if (std::find(intersection_previous->begin(), intersection_previous->end(), *potato_it) !=
                intersection_previous->end()) {
                list<PathComponent *> *start_path_comp_prev_version = new list<PathComponent *>();
                start_path_comp_prev_version->push_back(new PathComponent(*potato_it, '*'));
                search_paths(start_path_comp_prev_version, all_paths, intersection_previous,
                             intersection_next,
                             potato);
            }
            if (std::find(intersection_next->begin(), intersection_next->end(), *potato_it) !=
                    intersection_next->end()) {
                list<PathComponent *> *start_path_comp_next_version = new list<PathComponent *>();
                start_path_comp_next_version->push_back(new PathComponent(*potato_it, '+'));
                search_paths(start_path_comp_next_version, all_paths, intersection_previous,
                             intersection_next,
                             potato);
            }
        }
        return all_paths;
    }

    list<Signature*>* PotatoesSolver::paths_to_Signatures(list<list<PathComponent*>*>* paths){
        list<Signature*>* list_signatures = new list<Signature*>();
        list<list<PathComponent*>*>::iterator path_it;
        for (path_it = paths->begin(); path_it != paths->end(); path_it++){
            list_signatures->push_back(new Signature(*path_it));
        }

        return list_signatures;
    }


