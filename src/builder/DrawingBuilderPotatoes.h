//
// Created by julien on 12/10/16.
//

#ifndef GRAPH_DRAWINGBUILDERPOTATOES_H
#define GRAPH_DRAWINGBUILDERPOTATOES_H

#include <string>
#include "BuilderPotatoes.h"
using namespace std;

class DrawingBuilderPotatoes : public BuilderPotatoes {
public :

    static const string COLORS[];
    static  const int NB_AVAILABLE_COLOR = 6;

    void readPotatoes(list<list<Node *> *> *potatoes, size_t size_x, size_t size_y) override;
    string printArrayPotatoes();
    string printPotatoesDetail();
    void outputPotatoes(string output_path);


protected :
    list<list<Node*>*>* potatoes;
    size_t X;
    size_t Y;
};


#endif //GRAPH_DRAWINGBUILDERPOTATOES_H
