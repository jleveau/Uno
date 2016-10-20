//
// Created by julien on 09/10/16.
//

#include "CardReader.h"
#include <fstream>
#include <iostream>

using namespace std;

std::vector<Card *> * CardReader::readCards(const std::string path, int& nb_color, int& nb_number) {

    std::vector<Card*>* cards = new std::vector<Card*>();

    std::ifstream infile(path, ios::in);
    if (!infile){
        cout << "an error as occurred will reading card from: " << path << endl;
        exit(0);
    }
    int nb_card;
    int color, number;
    infile >> nb_card >> nb_color >> nb_number;

    while (infile >> color >> number) {
        Card *card = new Card(color, number);
        cards->push_back(card);
    }

    return cards;
}

CardReader::CardReader() {

}

CardReader::~CardReader() {

}



