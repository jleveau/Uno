#include <iostream>
#include <dirent.h>
#include <cstring>
#include "src/solvers/Solver.h"
#include "src/solvers/BruteSolver.h"
#include "src/solvers/PotatoesSolver.h"
#include "src/solvers/ProbabilisticSolver.h"

using namespace std;
int main(int argc, char* argv[]) {
    if (argc == 0){
        cout << "Usage : directory-of-decks output_path solver [k] \n"
                "solver : 0 = BRUTE "
                "solver : 1 = Potatoes "
                "solver : 2 = Probabilistic ";
        return 1;
    }
        if (argc < 4) {
        cout << "Invalid number of argument, must be : <input_path> <output_path> [solver]";
        return 1;
    }
    if (atoi(argv[3]) == 2 && argc < 5) {
        cout << "Invalid number of argument, must be : <input_path> <output_path> [solver] k";
        return 1;
    }

    string input_path = argv[1];
    string output_path = argv[2];
    Solver* solver;

    switch (atoi(argv[3])){
        case Solver::BRUTE:
            solver = new BruteSolver();
            break;
        case Solver::POTATOES:
            solver = new PotatoesSolver();
            break;
        case Solver::PROBABILISTIC:
            solver = new ProbabilisticSolver(atoi(argv[4]));
            break;
        default:
            solver = new PotatoesSolver();
    }

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (input_path.c_str())) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            if (strcmp(ent->d_name,".") == 0 || strcmp(ent->d_name,"..") ==0)
                continue;
            solver->setInput_path(input_path + "/" + ent->d_name);
            solver->setOutput_path(output_path + "/" + ent->d_name);
            solver->solve();
        }
        closedir (dir);
    } else {
        perror ("cannot open the input directory");
        return EXIT_FAILURE;
    }

    delete solver;
    return 0;
}