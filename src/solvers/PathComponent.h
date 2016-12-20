//
// Created by julien on 08/12/16.
//

#ifndef GRAPH_PATHCOMPONENT_H
#define GRAPH_PATHCOMPONENT_H

#include "../graph/Node.h"

class PathComponent {

private:
    Node* node;
    char separator;

public:
    Node *getNode() const;

    char getSeparator() const;

    PathComponent(Node *node);

    PathComponent(Node *node, char separator);
    std::string toString();
};


#endif //GRAPH_PATHCOMPONENT_H
