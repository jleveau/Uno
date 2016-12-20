//
// Created by julien on 09/10/16.
//

#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H


#include <vector>
#include <set>
#include <string>
#include <list>

class Node {

public:
    Node();

    int getColor() const;
    int getNumber() const;


    Node(int color, int number);

    std::set<Node *> *getNeighbors() const;
    std::list<Node *> * getUnmarkedNeighbors() const;


    bool isMarked() const;
    void setMarked(bool marked);

    void link_with(Node *pNode);
    std::string toString();

private:
    std::set<Node*>* neighbors;
    int color;
    int number;
    bool marked;
    int label;
public:
    int getLabel() const;

    void setLabel(int label);
};




#endif //GRAPH_NODE_H
