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
    int length;

public:

    Signature(list<PathComponent *> *components);

    Signature(list<PathComponent *> *components, int length);

    Signature* createPastVesion();
    Signature* createFutureVersion(list<Node*>* intersection_next);

    virtual ~Signature();

    Signature * merge(Signature* past_signature);

    list<PathComponent *> *getComponents() const;

    void setComponents(list<PathComponent *> *components);

    string toString();

    bool match(Signature *past_signature);
};


#endif //GRAPH_SIGNATURE_H


