//
// Created by julien on 12/10/16.
//

#include "PotatoesSolver.h"
#include "../cards/CardReader.h"
#include "../builder/GraphBuilder.h"
#include "../builder/DrawingBuilderPotatoes.h"
#include "Signature.h"

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
    generate_paths(potatoes);
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

list<Node *> *PotatoesSolver::generate_paths(list<list<Node *> *> *potatoes) {
    list<list<Node *> *>::iterator potatoes_it1;
    list<list<Node *> *>::iterator potatoes_it2;
    list<list<Node *>*> * paths = new list<list<Node *>*>();
    set<Node *>* intersection = new  set<Node *>();
    set<Signature*>* signatures = new set<Signature*>();

    intersect_potatoes(intersection,*potatoes_it1, *potatoes_it2);
    generate_signature(signatures,intersection,*potatoes_it1, *potatoes_it2);


    /*for (potatoes_it1 = potatoes->begin(); potatoes_it1 != potatoes->end(); ++potatoes_it1){
        potatoes_it2 = potatoes_it1;
        potatoes_it2++;
        list<Node *> * potato1 = *potatoes_it1;

        for (;potatoes_it2 != potatoes->end(); potatoes_it2++){
            list<Node *> * potato2 = *potatoes_it2;
            paths->merge(*path_intersect_potatoes(potato1,potato2));

        }
    }*/
}



set<Node *>*  PotatoesSolver::intersect_potatoes(set<Node *>* intersection, list<Node *> *potato1, list<Node *> *potato2) const {

    list<Node*>::iterator node_iterator1;
    list<Node*>::iterator node_iterator2;

    for (node_iterator1 = potato1->begin(); node_iterator1 != potato1->end(); node_iterator1++){
        for(node_iterator2 = potato2->begin(); node_iterator2 != potato2->end(); node_iterator2++){ if (*node_iterator1 == *node_iterator2)
                intersection->insert(*node_iterator1);
        }
    }
    return intersection;
}

void PotatoesSolver::generate_signature(set<Signature *> *signatures, set<Node *> *intersection, list<Node *> *potato1,
                                        list<Node *> *potato2) {
    generate_paths()
    Node* start_node = potato1->front();


}
