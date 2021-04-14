//
// Created by sofia on 14.04.2021.
//

#ifndef UNTITLED4_PACK_H
#define UNTITLED4_PACK_H

#endif //UNTITLED4_PACK_H

#include <vector>
#include "Card.h"

class Pack {
public:
    Pack() = default;

    Card* operator[](size_t ind);

    void push_front(Card* card);
    void pop_front();
    Card* head() const;

    size_t size() const;

    const static int numberOfPacks;

private:
    size_t size_ = 0;
    std::vector<Card*> cards_;

};