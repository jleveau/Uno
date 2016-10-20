//
// Created by julien on 09/10/16.
//

#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#include <set>
#include <list>
#include "Node.h"
#include "Edge.h"
#include "vector"

class Graph{
public:
    //Constructors
    Graph();
    Graph(std::set<Node *>* &nodes);
    virtual ~Graph();

    //Accessors
    std::set<Node *>* getNodes() const;
    void setNodes(std::set<Node *>* nodes);
    virtual void addNode(Node *n);

    //Methods
    std::list<std::list<Node*>*>* potatoesDFS();
    std::string toString();
    void unMarkNodes();

private:
    //Attributes
    std::set<Node *>* nodes ;

    //Methods
    void create_potatoes(Node *node, std::list<std::list<Node *> *> *potatoes_list, std::list<Node *> *node_list);
};




#endif //GRAPH_GRAPH_H
