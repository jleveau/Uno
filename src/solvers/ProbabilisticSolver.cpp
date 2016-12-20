//
// Created by julien on 20/12/16.
//

#include <iostream>
#include "ProbabilisticSolver.h"
#include "math.h"
#include <algorithm>

using namespace std;

ProbabilisticSolver::ProbabilisticSolver(const std::string &input_path, const std::string &output_path, int k) : Solver(
        input_path, output_path) {

}

ProbabilisticSolver::~ProbabilisticSolver() {
    delete graph;
    std::vector<Card *>::iterator it;
    for (it = cards->begin();it != cards->end(); ++it)
        delete *it;
    delete cards;
}

ProbabilisticSolver::ProbabilisticSolver(int k) {
    card_reader = new CardReader();
    builder = new GraphBuilder();
    this->k = k;
    this->max_it = exp(k);
}

void ProbabilisticSolver::solve() {
    int nb_color, nb_number;

    cards = card_reader->readCards(input_path, nb_color, nb_number);

    //Create the graph from the cards
    builder->setup(nb_color,nb_number);
    builder->read_cards(cards);
    graph = builder->build_graph();

    int i = 0;
    list<int>* colors = new list<int>();
    for (;i<k; i++){
        colors->push_back(i);
    }
    i=0;
    list<Node*>* longest_path = new list<Node*>();

    bool found = false;

    while (i < max_it && !found){
        graph -> applyRandomColor(k);
        set<Node*>* nodes = graph->getNodes();
        set<Node*>::iterator node_it;
        for (node_it = nodes->begin(); node_it != nodes->end(); node_it++){
            list<Node*>* path_current = new list<Node*>();
            list<int>* S = new list<int>();
            S->resize(colors->size());
            copy(colors->begin(), colors->end(), S->begin());

            list<Node*>* tmp = path(*node_it, S, path_current);
            if (tmp){
                longest_path = tmp;
                found = true;
                break;
            }
            delete S;
            delete path_current;
        }
        ++i;
    }
    if (found){
        list<Node*>::iterator path_it;
        cout << "path of size " << k <<  " found at iteration : " << i << endl;
        for (path_it = longest_path->begin(); path_it != longest_path->end(); path_it++){
            cout << (*path_it)->toString() << " ";
        }
    }
    else{
        cout << "no path, iteration reached : " << i;
    }
    delete longest_path;
    delete colors;
}

list<Node*>* ProbabilisticSolver::path(Node *const node, std::list<int>* S, list<Node*>* path_followed) {

    if (find(S->begin(), S->end(), node->getLabel()) == S->end()) {
        return 0;
    }
    path_followed->push_back(node);

    if (S->size() == 1 && S->front() == node->getLabel()) {
        return path_followed;
    }

    //s = S/{c(u)}
    set<Node *>::iterator neighbors_it = node->getNeighbors()->begin();
    for (; neighbors_it !=  node->getNeighbors()->end(); neighbors_it++){
        //store path
        list<Node*>* path_followed_next = new list<Node*>();
        path_followed_next->resize(path_followed->size());
        copy(path_followed->begin(), path_followed->end(), path_followed_next->begin());

        //store colors
        list<int>* S_next = new list<int>();
        S_next->resize(S->size());
        copy(S->begin(), S->end(), S_next->begin());
        S_next->remove(node->getLabel());
        list<Node*>* res = path(*neighbors_it, S_next, path_followed_next);


        delete S_next;

        if (res){
            return res;
        }
        delete path_followed_next;
    }
    return 0;
}


