//
// Created by julien on 09/10/16.
//

#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H


#include <vector>
#include <set>
#include <string>

class Node {

public:
    Node();

    int getColor() const;

    void setColor(int color);

    int getNumber() const;

    void setNumber(int number);

    Node(int color, int number);

    std::set<Node *> *getNeighbors() const;

    void setNeighbors(std::set<Node *> *neighbors);

    bool isMarked() const;

    void setMarked(bool marked);

    void link_with(Node *pNode);
    std::string toString();
    bool isLeaf();

private:
    std::set<Node*>* neighbors;
    int color;
    int number;
    bool marked;
};




#endif //GRAPH_NODE_H
