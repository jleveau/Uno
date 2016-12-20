//
// Created by julien on 20/12/16.
//

#ifndef GRAPH_PROBABILISTICSOLVER_H
#define GRAPH_PROBABILISTICSOLVER_H


#include "Solver.h"
#include "../graph/Graph.h"
#include "../cards/Card.h"
#include "../builder/GraphBuilder.h"
#include "../cards/CardReader.h"

class ProbabilisticSolver  : public Solver {
public:
    ProbabilisticSolver(const std::string &input_path, const std::string &output_path, int k);

    ProbabilisticSolver(int k);

    virtual ~ProbabilisticSolver();

    virtual void solve() override;

private:
    Graph* graph;
    int k;

    std::vector<Card *> * cards;
    GraphBuilder *builder;
    CardReader* card_reader;
    double max_it;

    std::list<Node *> * path(Node *const node, std::list<int> *S, std::list<Node *> *path);
};




#endif //GRAPH_PROBABILISTICSOLVER_H
