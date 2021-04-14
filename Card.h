//
// Created by sofia on 14.04.2021.
//

#ifndef UNTITLED4_CARD_H
#define UNTITLED4_CARD_H

#endif //UNTITLED4_CARD_H

///home/sofia/CLionProjects/untitled4/Card.h

#include <vector>


class Card {

public:
    size_t id;
    int rank;
    Card(int rank);

    const static int MAX_RANK;
    const static int MIN_RANK;

private:
    static size_t counter_; // = 0

};