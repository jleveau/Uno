//
// Created by julien on 20/10/16.
//

#include "Signature.h"

const set<Node *> &Signature::getIntersection() const {
    return intersection;
}

void Signature::setIntersection(const set<Node *> &intersection) {
    Signature::intersection = intersection;
}

const set<Node *> &Signature::getExcluded() const {
    return excluded;
}

void Signature::setExcluded(const set<Node *> &excluded) {
    Signature::excluded = excluded;
}

char Signature::getType() const {
    return type;
}

void Signature::setType(char type) {
    Signature::type = type;
}