//
// Created by sofia on 14.04.2021.
//

#include "Pack.h"

const int Pack::numberOfPacks_ = 8;


void Pack::pop_front() {
    cards_.pop_back();
}

void Pack::push_front(Card* card) {
    cards_.push_back(card);
}

size_t Pack::size() const {
    return size_;
}

Card* Pack::head() const {
    return cards_.back();
}

Card* Pack::operator[](size_t ind) {
    return cards_[ind];
}
