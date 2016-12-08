//
// Created by julien on 12/10/16.
//

#include <iostream>
#include "PotatoesSolver.h"
#include "../cards/CardReader.h"
#include "../builder/GraphBuilder.h"
#include "../builder/DrawingBuilderPotatoes.h"
#include "Signature.h"
#include "PathComponent.h"
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

    //Output the result
   // DrawingBuilderPotatoes* drawingBuilderPotatoes = new DrawingBuilderPotatoes();
   // drawingBuilderPotatoes -> readPotatoes(potatoes,nb_color,nb_number);
   // drawingBuilderPotatoes -> outputPotatoes(output_path);

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
    list<list<Node *> *>::iterator potatoes_it1 = potatoes->begin();

    std::set<Signature*>* signatures = new std::set<Signature*>();
  //  signatures->insert(new Signature());

    list<Node *>* current_potatoe = *potatoes_it1;
    list<Node *>* next_potatoe = *(potatoes_it1++);

    //Print
    /*
    list<Node*>* intersection = intersect_potatoes(current_potatoe, next_potatoe);
    list<Node*>::iterator current_it = intersection->begin();
    for (intersection; current_it!=intersection->end(); ++current_it){
        std::cout << (*current_it)->toString() << endl;
    }
     */
    //END print

}

/*
 * Retourne l'intersection de deux patates
 */
list<Node*>* PotatoesSolver::intersect_potatoes(list<Node *> *current_potatoe, list<Node *> *next_potatoe) {
    list<Node*>::iterator current_it = current_potatoe->begin();
    list<Node*>::iterator next_it = next_potatoe->begin();
    list<Node*>* intersection = new list<Node*>();

    for(;current_it != current_potatoe->end(); ++current_it){
        for(;next_it != next_potatoe->end(); next_it++){
            if (current_it == next_it){
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
list<list<PathComponent*>*>* search_paths(list<PathComponent*>* path, list<list<PathComponent*>*>* all_paths,
                                          list<Node*>* intersection_previous ,list<Node*>* intersection_next ){
    Node* current = path->back()->getNode();
    set<Node*>::iterator neighbors_it;
    set<Node*>* neighbors = current->getNeighbors();
    if (neighbors->empty()){
        return all_paths;
    }
    for (neighbors_it = neighbors->begin(); neighbors_it != neighbors->end(); neighbors_it++){
        list<PathComponent *>* new_path = new std::list<PathComponent *>();
        new_path->resize(path->size());
        copy(path->begin(), path->end(), new_path->begin());
        new_path->push_back(new PathComponent((*neighbors_it),'-'));

        list<list<PathComponent*>*>* new_paths = search_paths(new_path, all_paths,
                                                              intersection_previous, intersection_next);
        all_paths->insert(all_paths->end(), new_paths->begin(), new_paths->end());
    }

    if (std::find(intersection_next->begin(), intersection_next->end(), current) != intersection_next->end()){
        list<Node*>::iterator intersection_it;
        for (intersection_it = intersection_next ->begin(); intersection_it != intersection_next->end(); ++intersection_it){
            if (current != *intersection_it){
                list<PathComponent *>* new_path = new std::list<PathComponent *>();
                new_path->resize(path->size());
                copy(path->begin(), path->end(), new_path->begin());
                new_path->push_back(new PathComponent((*neighbors_it),'+'));

                list<list<PathComponent*>*>* new_paths = search_paths(new_path, all_paths,
                                                                      intersection_previous, intersection_next);
                all_paths->insert(all_paths->end(), new_paths->begin(), new_paths->end());
            }
        }
    }
    if (std::find(intersection_previous->begin(), intersection_previous->end(), current) != intersection_previous->end()){
        list<Node*>::iterator intersection_it;
        for (intersection_it = intersection_previous ->begin(); intersection_it != intersection_previous->end(); ++intersection_it){
            if (current != *intersection_it){
                list<PathComponent *>* new_path = new std::list<PathComponent *>();
                new_path->resize(path->size());
                copy(path->begin(), path->end(), new_path->begin());
                new_path->push_back(new PathComponent((*neighbors_it),'*'));

                list<list<PathComponent*>*>* new_paths = search_paths(new_path, all_paths,
                                                                      intersection_previous, intersection_next);
                all_paths->insert(all_paths->end(), new_paths->begin(), new_paths->end());
            }
        }
    }
    return all_paths;
}

/*
 * return all paths using recursion
 * we must use the previous intersection to define the "*" paths
 * and next intersection to define "+" paths
 */
list<list<PathComponent*>*>* PotatoesSolver::allPaths(list<Node*>* potato, list<Node*>* intersection_previous
                                                                            , list<Node*>* intersection_next){
    list<list<PathComponent*>*>* all_paths = new list<list<PathComponent*>*>();
    list<Node*>::iterator potato_it;

    for (potato_it = potato->begin(); potato_it != potato->end(); potato_it++){
        list<PathComponent*>* start_path_comp = new list<PathComponent*>();
        start_path_comp->push_back(new PathComponent(*potato_it,'0'));
        list<list<PathComponent*>*>* new_paths = search_paths(start_path_comp, all_paths,
                                                              intersection_previous,
                                                              intersection_next);

        all_paths->insert(all_paths->end(), new_paths->begin(), new_paths->end());
    }
    return all_paths;
}