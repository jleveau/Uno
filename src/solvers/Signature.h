//
// Created by julien on 20/10/16.
//

#ifndef GRAPH_SIGNATURE_H
#define GRAPH_SIGNATURE_H


#include <list>
#include "../graph/Node.h"
#include "PathComponent.h"

using namespace std;
class Signature {
private :

    list<PathComponent*>* components;
public:

    Signature(list<PathComponent *> *components);
    Signature* createPastVesion();
    Signature* createFutureVersion();

    virtual ~Signature();
};


#endif //GRAPH_SIGNATURE_H

Signature::Signature(list<PathComponent *> *components) : components(components) {}


Signature::~Signature() {
    list<PathComponent*>::iterator component_it;

    for (component_it = components->begin(); component_it != components->end(); ++component_it){
        delete *component_it;
    }
    delete components;
}


