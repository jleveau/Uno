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
    CardReader* card_reader;
    DrawingBuilderPotatoes* drawingBuilderPotatoes;

    list<Node *> * intersect_potatoes(list<Node *> *pList, list<Node *> *potato);
    void mergeSignatures(list<Signature *> *signatures_current, list<Signature *> *signatures_past);
    list<Signature*>* paths_to_Signatures(list<list<PathComponent*>*>* paths);
    list<list<PathComponent *> *> *allPaths(list<Node *> *potato, list<Node *> *intersection_previous,
                                                            list<Node *> *intersection_next);

public:
    virtual ~PotatoesSolver();
    list<Node *> *longest_path(list<list<Node *> *> *pList);

};



#endif //GRAPH_POTATOESSOLVER_H
