//
// Created by sofia on 14.04.2021.
//

#ifndef UNTITLED4_SOLVER_H
#define UNTITLED4_SOLVER_H

#endif //UNTITLED4_SOLVER_H

#include "State.h"

#include "Pack.h"

class Solver {
public:

    void getIntput();
    bool findAnswer();
    bool recursivelyTryToSuccess(int rank_to_search = Card::MAX_RANK + 1, int packid_to_built_set_of_9_cards = -1);
    returnedState tryToPullCardFromPack(int card_ind, int pack_ind_from, int pack_int_to, std::vector<Pack>&packes);
    int heuristicFunction(int card_ind, int pack_ind,  std::vector<Pack>& packs);

    Solver();

private:
    std::vector<Card> all_cards_;
    std::vector<Pack> all_packes;
    std::vector<int> all_rangs;

    using Card::;
};