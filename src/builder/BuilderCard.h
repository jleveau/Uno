//
// Created by julien on 10/10/16.
//

#ifndef GRAPH_BUILDER_H
#define GRAPH_BUILDER_H


#include "../cards/Card.h"
#include "../graph/Graph.h"
#include "vector"

class BuilderCard {
public:
    virtual void read_card(Card* const card) = 0;
    virtual void read_cards(std::vector<Card*>* cards) = 0;
};


#endif //GRAPH_BUILDER_H
