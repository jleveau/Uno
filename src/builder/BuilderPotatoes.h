//
// Created by julien on 12/10/16.
//

#ifndef GRAPH_BUILDERPOTATOES_H
#define GRAPH_BUILDERPOTATOES_H

#include "../graph/Node.h"
#include "list"

using namespace std;

class BuilderPotatoes {
    virtual void readPotatoes(list<list<Node*>*>* potatoes, size_t size_x, size_t size_y) = 0;
};


#endif //GRAPH_BUILDERPOTATOES_H
