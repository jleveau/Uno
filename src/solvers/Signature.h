//
// Created by julien on 20/10/16.
//

#ifndef GRAPH_SIGNATURE_H
#define GRAPH_SIGNATURE_H


#include "../graph/Node.h"
using namespace std;
class Signature {
private :
    set<Node*> intersection;
    set<Node*> excluded;
    char type;
public:
    const set<Node *> &getIntersection() const;

    void setIntersection(const set<Node *> &intersection);

    const set<Node *> &getExcluded() const;

    void setExcluded(const set<Node *> &excluded);

    char getType() const;

    void setType(char type);

};


#endif //GRAPH_SIGNATURE_H


