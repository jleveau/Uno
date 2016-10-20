//
// Created by julien on 09/10/16.
//

#ifndef GRAPH_CARD_H
#define GRAPH_CARD_H


#include <string>

class Card {
public:
    int getColor() const;

    void setColor(int color);

    int getNumber() const;

    void setNumber(int number);

public:
    Card(int color, int number);
    std::string toString();

private:
    int color;
    int number;


};


#endif //GRAPH_CARD_H
