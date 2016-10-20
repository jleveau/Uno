//
// Created by julien on 12/10/16.
//

#include <sstream>
#include <iostream>
#include "BruteSolver.h"

using namespace std;


BruteSolver::BruteSolver(const std::string &input_path, const std::string &output_path) : Solver(input_path,
                                                                                                 output_path) {

}

BruteSolver::BruteSolver() : Solver() {

}

void BruteSolver::solve() {

    ostringstream oss;
    cout << oss.str() << endl << flush;

    oss << BINARY << " " << input_path << " " << output_path;
    if (int err = !(system(oss.str().c_str())==0))
        cerr << "something went wrong during brute force execution : " << err ;
}
