//
// Created by julien on 12/10/16.
//

#ifndef GRAPH_SOLVER_H
#define GRAPH_SOLVER_H


#include <string>
#include "SolverItf.h"

class Solver : public SolverItf {

public:
    static const int BRUTE = 0;
    static const int POTATOES = 1;
    static const int PROBABILISTIC = 2;

    const std::string &getInput_path() const;

    const std::string &getOutput_path() const;

    Solver(const std::string &input_path, const std::string &output_path);
    Solver();

    virtual void solve() = 0;

    void setInput_path(const std::string &input_path);

    void setOutput_path(const std::string &output_path);

protected :
    std::string input_path;
    std::string output_path;
};


#endif //GRAPH_SOLVER_H
