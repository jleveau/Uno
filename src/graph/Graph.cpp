//
// Created by julien on 09/10/16.
//

#include <string>
#include "Node.h"
#include "Graph.h"
#include <sstream>
#include <iostream>
#include <random>
#include <algorithm>

using namespace std;
Graph::Graph(std::set<Node *>* &nodes) : nodes(nodes) {}


std::set<Node *>* Graph::getNodes() const {
    return nodes;
}

void Graph::setNodes(std::set<Node *>* nodes) {
    this->nodes = nodes;
}

void Graph::addNode(Node* n) {
    if (nodes == nullptr)
        return;
    this->nodes->insert(n);
}

Graph::~Graph() {
    std::set<Node *>::iterator it;
    for (it = nodes->begin();it != nodes -> end() ; ++it)
        delete *it;
    delete(nodes);
}

std::string Graph::toString() {
    if (nodes == nullptr)
        return "null";
    std::set<Node*>::const_iterator i;
    std::ostringstream oss;

    for(i=nodes->begin();i!=nodes->end();++i){
        Node* n = *i;
        oss << n->toString() << std::endl;
    }
    return oss.str();

}

std::list<std::list<Node *> *> *Graph::potatoesDFS() {
    if (nodes == nullptr)
        return nullptr;
    std::list<std::list<Node *> *> *potatoes_list;
    std::list<Node *>* potato;
    std::list<Node *>* node_list =new std::list<Node *>();


    potatoes_list = new std::list<std::list<Node *> *>();


    //We dupliate the graph list of nodes (because we will pop it to build potatoes)
    node_list->resize(nodes->size());
    copy(nodes->begin(),nodes->end(),node_list->begin());

    while (!node_list->empty()) {
        //Start a new potato
        potato = new std::list<Node *>();
        potatoes_list->push_back(potato);


        Node *n = *node_list->begin(); //we take an arbitrary first node.
        create_potatoes(n, potatoes_list, node_list);
    }
    return potatoes_list;
}

void Graph::create_potatoes(Node *node, std::list<std::list<Node *> *> *potatoes_list, std::list<Node *> *node_list) {
    if (node == nullptr)
        return;

    //Add the node to the current potato
    std::list<Node *> * potato = potatoes_list->back();
    std::list<Node *> * current_potato = nullptr;

    potato->push_back(node);
    node_list->remove(node);
    node->setMarked(true);

    //Continue to build the current potato
    std::set<Node *> *neighbors = node->getNeighbors();
    std::set<Node *>::iterator neighbors_it;
    if (neighbors->begin() == neighbors->end()){
        return;
    }
    if (neighbors->size() > 1) {

        current_potato = new std::list<Node *>();
        current_potato->resize(potato->size());
        copy(potato->begin(), potato->end(), current_potato->begin());
    }
    for (neighbors_it = neighbors->begin(); neighbors_it != neighbors->end(); neighbors_it++){
        if (!((*neighbors_it)->isMarked())){
            create_potatoes(*neighbors_it, potatoes_list, node_list);
            break;
        }
    }
    //And start a new potato for each other neighbor
    for (; neighbors_it != neighbors->end(); neighbors_it++){
        if (!(*neighbors_it) -> isMarked()){
            std::list<Node *> * new_potato = new std::list<Node *> ();
            new_potato->resize(current_potato->size());
            copy(current_potato->begin(),current_potato->end(),new_potato->begin());

            potatoes_list->push_back(new_potato);
            create_potatoes(*neighbors_it, potatoes_list, node_list);
        }
    }
    if (current_potato != nullptr){
        delete current_potato;
    }
}

void Graph::unMarkNodes() {
    if (nodes == nullptr)
        return;
    std::set<Node *>::iterator nodes_it;
    for (nodes_it = nodes->begin(); nodes_it != nodes->end(); nodes_it++)
        (*nodes_it)->setMarked(false);
}

void Graph::applyRandomColor(int i) {
    const int range_from  = 0;
    const int range_to    = i-1;
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>  distr(range_from, range_to);

    std::set<Node *>::iterator nodes_it;

    for (nodes_it = nodes->begin(); nodes_it != nodes->end(); nodes_it++) {
        int color = distr(generator);
        (*nodes_it)->setLabel(color);
    }
}
