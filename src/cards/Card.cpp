//
// Created by julien on 09/10/16.
//

#include "Card.h"
#include <iostream>
#include <sstream>

Card::Card(int color, int number) : color(color), number(number) {}

std::string Card::toString() {

    std::ostringstream oss;
    oss << "color : " << color << ", number : " << number;
    return oss.str();
}

int Card::getColor() const {
    return color;
}

void Card::setColor(int color) {
    Card::color = color;
}

int Card::getNumber() const {
    return number;
}

void Card::setNumber(int number) {
    Card::number = number;
}

