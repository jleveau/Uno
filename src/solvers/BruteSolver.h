//
// Created by julien on 12/10/16.
//

#ifndef GRAPH_BRUTESOLVER_H
#define GRAPH_BRUTESOLVER_H


#include "Solver.h"

class BruteSolver : public Solver{
public:

    BruteSolver(const std::string &input_path, const std::string &output_path);

    BruteSolver();

    virtual void solve() override;

private:
    const std::string BINARY = "~/ClionProjects/Graph/resources/brute";
};


#endif //GRAPH_BRUTESOLVER_H
