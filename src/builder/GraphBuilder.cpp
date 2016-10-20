//
// Created by julien on 10/10/16.
//

#include <iostream>
#include "GraphBuilder.h"

using namespace std;

GraphBuilder::GraphBuilder(int nb_color, int nb_number):GraphBuilder() {
    setup(nb_color,nb_number);
}

void GraphBuilder::read_card(Card *const card) {
    Node* node = new Node(card->getColor(),card->getNumber());

    node_by_color->operator[](card->getColor())->push_back(node);
    node_by_number->operator[](card->getNumber())->push_back(node);
    nodes->insert(node);
}


void GraphBuilder::setup(int nb_color, int nb_number) {
    this->nb_color=nb_color;
    this->nb_number=nb_number;

    int i=0;

    this->node_by_number = setup_node_vector(this->node_by_number);
    this->node_by_color = setup_node_vector(this->node_by_color);

    for (i; i<nb_color;i++) {
        this->node_by_color->push_back(new list<Node *>());
    }

    for (i=0; i<nb_number;i++)
        this->node_by_number->push_back(new list<Node*>());

    this->nodes = new set<Node*>();
}

vector<list<Node *> *> * GraphBuilder::setup_node_vector(vector<list<Node*>*>* _vector){
    if (_vector == nullptr)
        _vector = new vector<list<Node*>*>();
    else
        while(!_vector->empty()){
            delete _vector->back();
            _vector->pop_back();
        }
    return _vector;
}

void GraphBuilder::read_cards(std::vector<Card *> *cards) {
    std::vector<Card*>::const_iterator i;
    for(i=cards->begin(); i!=cards->end(); ++i){
        read_card(*i);
    }
}

Graph* GraphBuilder::build_graph() {
    link_nodes();
    return new Graph(nodes);
}

GraphBuilder::~GraphBuilder() {
    int i=0;
    for (i; i<nb_color;i++) {
        delete (*node_by_color)[i];
    }
    for (i=0; i<nb_number;i++) {
        delete (*node_by_number)[i];
    }
    delete node_by_color;
    delete node_by_number;
    delete nodes;
}

void GraphBuilder::link_from_list(std::list<Node*>* nodes){
    std::list<Node*>::const_iterator node;
    std::list<Node*>::const_iterator i;
    if (nodes -> empty())
        return;
    for (node = nodes->begin(); node != nodes->end(); node++){
        for (i = nodes->begin(); i != nodes->end(); i++){
            if (*i != *node)
              (*node)->link_with(*i);
        }
    }
}

void GraphBuilder::link_nodes() {

    for (int color_iterator = 0; color_iterator < nb_color; color_iterator++){
        list<Node*>* list_color = (*node_by_color)[color_iterator];
        link_from_list(list_color);
    }
    for (int number_iterator = 0; number_iterator < nb_number; number_iterator++){
        list<Node*>* list_number= (*node_by_number)[number_iterator];
        link_from_list(list_number);
    }

}

GraphBuilder::GraphBuilder() {

}

