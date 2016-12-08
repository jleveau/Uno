//
// Created by julien on 12/10/16.
//

#ifndef GRAPH_POTATOESSOLVER_H
#define GRAPH_POTATOESSOLVER_H


#include "Solver.h"
#include "../graph/Graph.h"
#include "../cards/Card.h"
#include "../cards/CardReader.h"
#include "../builder/DrawingBuilderPotatoes.h"
#include "../builder/GraphBuilder.h"
#include "Signature.h"
#include "PathComponent.h"

class PotatoesSolver : public Solver {
protected:
public:
    PotatoesSolver();

    PotatoesSolver(const std::string &input_path, const std::string &output_path);

    virtual void solve() override;
private :
    Graph* graph;
    std::vector<Card *> * cards;
    GraphBuilder *builder;
public:
    virtual ~PotatoesSolver();

private:
    CardReader* card_reader;
    DrawingBuilderPotatoes* drawingBuilderPotatoes;

    list<Node *> *longest_path(list<list<Node *> *> *pList);


    list<Node *> * intersect_potatoes(list<Node *> *pList, list<Node *> *potato);

    list<list<PathComponent *> *> *
    allPaths(list<Node *> *potato, list<Node *> *intersection_previous, list<Node *> *intersection_next);
};



#endif //GRAPH_POTATOESSOLVER_H
