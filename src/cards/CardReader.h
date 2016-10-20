//
// Created by julien on 09/10/16.
//

#ifndef GRAPH_CARDREADER_H
#define GRAPH_CARDREADER_H


#include <string>
#include "Card.h"
#include "vector"


class CardReader {
public:
    std::vector<Card *> *readCards(const std::string path, int &nb_color, int &nb_number);

    CardReader();

    virtual ~CardReader();

protected:

private:

};


#endif //GRAPH_CARDREADER_H
