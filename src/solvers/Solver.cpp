//
// Created by julien on 12/10/16.
//

#include "Solver.h"

Solver::Solver(const std::string &input_path, const std::string &output_path) : input_path(input_path),
                                                                                output_path(output_path) {}

Solver::Solver() {}

const std::string &Solver::getInput_path() const {
    return input_path;
}

const std::string &Solver::getOutput_path() const {
    return output_path;
}

void Solver::setInput_path(const std::string &input_path) {
    Solver::input_path = input_path;
}

void Solver::setOutput_path(const std::string &output_path) {
    Solver::output_path = output_path;
}
