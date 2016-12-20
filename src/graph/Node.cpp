//
// Created by julien on 09/10/16.
//

#include <string>
#include <iostream>
#include <sstream>
#include <list>
#include "Node.h"
using namespace std;

void Node::link_with(Node *pNode) {
    neighbors->insert(pNode);
}

std::string Node::toString() {
    std::ostringstream oss;
    oss <<"(" <<  color << "," << number << ") ";
    return oss.str();
}

Node::Node() {
    neighbors = new std::set<Node *>();
    marked = false;
}

Node::Node(int color, int number) : color(color), number(number) {
    neighbors = new std::set<Node *>();
    marked=false;
}

set<Node *> *Node::getNeighbors() const {
    return neighbors;
}

bool Node::isMarked() const {
    return marked;
}

void Node::setMarked(bool marked) {
    Node::marked = marked;
}

int Node::getColor() const {
    return color;
}

int Node::getNumber() const {
    return number;
}

std::list<Node *> *Node::getUnmarkedNeighbors() const {
    std::list<Node*>* nodes = new std::list<Node*>();
    nodes->resize(neighbors->size());
    copy(neighbors->begin(), neighbors->end(), nodes->begin());

    std::list<Node*>::iterator it;
    for (it = nodes->begin(); it != nodes->end(); ++it){
        if ((*it)->isMarked()){
            nodes->remove(*it);
        }
    }
    return nodes;
}

int Node::getLabel() const {
    return label;
}

void Node::setLabel(int label) {
    Node::label = label;
}