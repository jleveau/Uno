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
public:
    virtual ~PotatoesSolver();

private:
    CardReader* card_reader;
    DrawingBuilderPotatoes* drawingBuilderPotatoes;

    list<Node *> *generate_paths(list<list<Node *> *> *pList);


    set<Node *> *intersect_potatoes(set<Node *> *intersection, list<Node *> *potato1, list<Node *> *potato2) const;

    void generate_signature(set<Signature *> *signatures, set<Node *> *intersection, list<Node *> *potato1,
                            list<Node *> *potato2);
};



#endif //GRAPH_POTATOESSOLVER_H
