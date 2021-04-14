//
// Created by sofia on 14.04.2021.
//
#include "Card.h"

const int Card::MAX_RANK = 14;
const int Card::MIN_RANK = 6;

size_t Card::counter_ = 0;

Card::Card(int rank): rank(rank) {
    id = counter_++;
}
