//
// Created by julien on 08/12/16.
//

#include "PathComponent.h"

PathComponent::PathComponent(Node *node) : node(node) {}

Node *PathComponent::getNode() const {
    return node;
}

char PathComponent::getSeparator() const {
    return separator;
}

PathComponent::PathComponent(Node *node, char separator) : node(node), separator(separator) {}
