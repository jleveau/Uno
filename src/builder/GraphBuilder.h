//
// Created by julien on 10/10/16.
//

#ifndef GRAPH_GRAPHBUILDER_H
#define GRAPH_GRAPHBUILDER_H


#include <set>
#include <list>
#include "BuilderCard.h"

class GraphBuilder : public BuilderCard{
public:


    GraphBuilder(int nb_color, int nb_number);

    virtual void read_card(Card *const card) override;

    virtual void read_cards(std::vector<Card *> *cards) override;
    Graph* build_graph();

    virtual ~GraphBuilder();
    void link_nodes();

    void setup(int nb_color, int nb_number);

    GraphBuilder();

private:
    int nb_number;
    int nb_color;

    std::set<Node*>* nodes;
    std::vector<std::list<Node*>*>* node_by_color;
    std::vector<std::list<Node*>*>* node_by_number;
    void link_from_list(std::list<Node *> *nodes);
    std::vector<std::list<Node *> *> * setup_node_vector(std::vector<std::list<Node *> *>*);
};


#endif //GRAPH_GRAPHBUILDER_H
