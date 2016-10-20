//
// Created by julien on 09/10/16.
//

#include <string>
#include <iostream>
#include <sstream>
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

void Node::setNeighbors(set<Node *> *neighbors) {
    Node::neighbors = neighbors;
}

bool Node::isLeaf(){
    if (neighbors == nullptr)
        return true;
    return neighbors->empty();
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

void Node::setColor(int color) {
    Node::color = color;
}

int Node::getNumber() const {
    return number;
}

void Node::setNumber(int number) {
    Node::number = number;
}
