//
// Created by julien on 20/10/16.
//

#include "Signature.h"
#include <algorithm>
#include <iostream>
#include <sstream>


Signature *Signature::createPastVesion() {
    /*
     *  - -> +
     *  + -> +
     *  * -> -
     *  il faut supprimer les nodes qui ne sont pas dans l'intersection
     */
    list<PathComponent*>* new_componds = new list<PathComponent*>();
    list<PathComponent*>::iterator components_it = components->begin();

    for (; components_it != components->end(); ++components_it){
        if ((*components_it)->getSeparator() == '-')
            new_componds->push_back(new PathComponent((*components_it)->getNode(), '+'));
        if ((*components_it)->getSeparator() == '+')
            new_componds->push_back(new PathComponent((*components_it)->getNode(), '+'));
        if ((*components_it)->getSeparator() == '*')
            new_componds->push_back(new PathComponent((*components_it)->getNode(), '-'));
    }
    return new Signature(new_componds, this->length);
}

Signature *Signature::createFutureVersion(list<Node*>* intersection_next) {
    /*
     * * -> -
     *  il faut supprimer les nodes hors intersection (sans +)
     */
    list<PathComponent*>* new_componds = new list<PathComponent*>();
    list<PathComponent*>::iterator components_it;
    for (components_it = components->begin(); components_it != components->end(); ++components_it) {
        if (std::find(intersection_next->begin(), intersection_next->end(), (*components_it)->getNode()) !=
            intersection_next->end()) {
            if ((*components_it)->getSeparator() == '*')
                new_componds->push_back(new PathComponent((*components_it)->getNode(), '-'));
            if ((*components_it)->getSeparator() == '-')
                new_componds->push_back(new PathComponent((*components_it)->getNode(), '-'));
            if ((*components_it)->getSeparator() == '+')
                new_componds->push_back(new PathComponent((*components_it)->getNode(), '+'));
        }
    }
    return new Signature(new_componds, this->length);
}

bool Signature::match(Signature* past_s){
    //cout << "merge past : " << (past_s)->toString() << endl << "with : " << this->toString() << endl ;

    if (past_s->components->size() != components->size())
        return false;
    list<PathComponent*>::iterator components_past_it = past_s->components->begin();
    list<PathComponent*>::iterator components_current_it = components->begin();

    while(components_current_it != components->end()){
        if ((*components_current_it)->getSeparator() == '*'){
            return false;
        }
        if ((*components_current_it)->getSeparator() == (*components_current_it)->getSeparator())
            return false;
        ++components_past_it;
        ++components_current_it;
    }
    return true;
}

Signature* Signature::merge(Signature *past_signature) {
    list<PathComponent*>* new_components = new list<PathComponent*>();

    new_components->resize(components->size());
    copy(components->begin(), components->end(), new_components->begin());
    return new Signature(new_components, length + past_signature->length);
}

Signature::Signature(list<PathComponent *> *components) : components(components) {
    this->length = components->size();
}

Signature::Signature(list<PathComponent *> *components, int length) : components(components), length(length) {}

Signature::~Signature() {
    list<PathComponent*>::iterator component_it;

    for (component_it = components->begin(); component_it != components->end(); ++component_it){
        delete *component_it;
    }
    delete components;
}

string Signature::toString() {
    list<PathComponent*>::iterator component_it;
    std::ostringstream oss;
    for (component_it = components->begin(); component_it != components->end(); ++component_it){
        oss << (*component_it)->toString();
    }
    oss << " : " << length << endl;
    return oss.str();
}

list<PathComponent *> *Signature::getComponents() const {
    return components;
}

void Signature::setComponents(list<PathComponent *> *components) {
    Signature::components = components;
}
