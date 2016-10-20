//
// Created by julien on 12/10/16.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "DrawingBuilderPotatoes.h"
#include "../../COLOR.h"


const string DrawingBuilderPotatoes::COLORS[] = {"fg_red" "fg_blue", "fg_green", "fg_purple", "fg_cyan", "fg_black"};

void DrawingBuilderPotatoes::readPotatoes(list<list<Node *> *> *potatoes, size_t size_x, size_t size_y) {
    this->potatoes=potatoes;
    X = size_x;
    Y = size_y;
}

void DrawingBuilderPotatoes::outputPotatoes(string output_path) {
    ofstream outfile;
    outfile.open (output_path);
    if (!outfile){
        cout << "an error as occurred will reading potatoes" << endl;
        exit(0);
    }
    outfile << printArrayPotatoes() << endl << printPotatoesDetail();
}


string DrawingBuilderPotatoes::printArrayPotatoes() {

    string colors[6] = { FBLU("1 "), FRED("1 "), FCYN("1 "), FYEL("1 "), FGRN("1 "), FWHT("1 ")};
    ostringstream oss;
    std::list<std::list<Node *> *>::const_iterator potatoes_it;
    std::list<Node *>::const_iterator node_it;


    int color_index = 0;
    string tab[X][Y];
    for (int j = 0; j < Y; ++j)
        for (int i=0; i < X ; ++i)
            tab[j][i] = "0 ";

    for (potatoes_it = potatoes->begin(); potatoes_it != potatoes->end(); potatoes_it++){
        std::list<Node *>* potato = *potatoes_it;
        for (node_it = potato->begin(); node_it != potato->end();node_it++){
            Node* node = *node_it;
            tab[node->getNumber()][node->getColor()] = colors[color_index%6];
        }
        ++color_index;
    }
    for (int j = 0; j < Y; ++j){
        for (int i=0; i < X ; ++i){
            oss << tab[j][i];
        }
        oss << endl;
    }
    return oss.str();
}

string DrawingBuilderPotatoes::printPotatoesDetail() {
    list<list<Node*>*>::iterator potatoes_iterator;
    list<Node*>::iterator nodes_iterator;

    ostringstream oss;
    oss << "number of potatoes : " << potatoes->size() << endl;
    int num =0;
    for (potatoes_iterator = potatoes->begin(); potatoes_iterator!= potatoes->end(); potatoes_iterator++) {
        list<Node*>* potato = *potatoes_iterator;
        oss << "potato number : " << num++ << endl;
        oss << "{";
        for (nodes_iterator = potato->begin(); nodes_iterator != potato->end();nodes_iterator++){
            Node* node = *nodes_iterator;
            oss << node->toString() << ",";
        }
        oss << "}" << endl ;
    }
    return oss.str();
}

