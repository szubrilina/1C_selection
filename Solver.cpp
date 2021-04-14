//
// Created by sofia on 14.04.2021.
//


#include "Solver.h"
#include <algorithm>
#include <set>
#include <functional>


Solver::Solver() {
    all_packes.resize(Pack::numberOfPacks);
    for (int i = Card::MIN_RANK; i <= Card::MAX_RANK; ++i) {
        all_rangs.push_back(i);
    }
};

void Solver::getIntput() {
    //TODO
}

bool Solver::findAnswer() {

    getIntput();

    bool result = recursivelyTryToSuccess();

    return result;
}

bool Solver::recursivelyTryToSuccess(int rank_to_search, int packid_to_built_set_of_9_cards) { //

    if (rank_to_search == Card::MAX_RANK) {
        //TODO or do the same
    }
    else {

        if (rank_to_search < MIN_RANK_) {
            return true;
        }


        std::vector<std::pair<int, std::pair<int, int>>> priorityAndCard_ind;

        //перебираем из какой колонны будем брать карту
        for (int pack_ind = 0; pack_ind < all_packes.size(); ++pack_ind) {
            if (pack_ind == packid_to_built_set_of_9_cards) { // тк psckid это номер колонны, на которой пытаемся собрать полный набор из 9 карт
                continue;
            }

            // перебираем какую именно карту из этой  колонны возьмем
            for (int card_ind = 0; card_ind < all_packes[pack_ind].size(); ++card_ind) {
                if (all_packes[pack_ind][card_ind]->rank != rank_to_search) {
                    continue;
                } // если она не нужного нам ранга, то продолжаем поиск

                std::vector<Pack> copy_of_packes = all_packes;
                returnedState st = tryToPullCardFromPack(card_ind, pack_ind, copy_of_packes);

                if (st.ifManaged) { // пытаемся как-то раскидать все карты лежащие над нашей
                    //если это возможно, то запонинаем, что именно из этой колонны мы вытянули эту карту, а также запомним
                    // значение эвристической функции
                    priorityAndCard_ind.push_back({st.heuristicFunctionReturn, {card_ind, pack_ind}});
                }
            }
        }
        std::sort(priorityAndCard_ind.begin(), priorityAndCard_ind.end());

        for (int i = priorityAndCard_ind.size() - 1; i >= 0; --i) {
            int card_ind = priorityAndCard_ind[i].second.first;
            int pack_ind = priorityAndCard_ind[i].second.second;

            std::vector<Pack> new_packes = all_packes;
            tryToPullCardFromPack(card_ind, pack_ind, packid_to_built_set_of_9_cards, new_packes);

            std::vector<Pack> old_packes = all_packes;
            all_packes = new_packes;

            if (recursivelyTryToSuccess(rank_to_search - 1, packid_to_built_set_of_9_cards)) {
                return true;
            }
            else {
                all_packes = old_packes;
                continue;
            }
        }
        //если не получилось положит на текущую коллоду ни одну карту нужного нам значения (ранга),
        // то мы не можем собрать полный набор из 9 карт
        return false;
    }
}


returnedState Solver::tryToPullCardFromPack(int card_ind, int pack_ind_from, int pack_ind_to,  std::vector<Pack>&packs) {

    bool isManagd = 1;


    for (int i = 0; i < card_ind; ++i) {
        Card* current_card = packs[pack_ind_from][i];

        int min_rang = -1;
        int minpack_ind = -1;

        for (int j = 0; j < packs.size(); ++i) {
            if (j == pack_ind_to) {
                continue;
            }
            if (packs[i].head()->rank > current_card->rank && packs[i].head()->rank < min_rang) {
                min_rang = packs[i].head()->rank;
                minpack_ind = j;
            }
        }

        if ( min_rang == -1) {
            isManagd = 0;
            break;
        }
        packs[minpack_ind].push_front(current_card);
        packs[pack_ind_from].pop_front();
    }

    if (!isManagd) {
        return returnedState{0, 0};
    }

    Card* my_card = packs[pack_ind_from].head();
    packs[pack_ind_from].pop_front();
    packs[pack_ind_to].push_front(my_card);

    int value = heuristicFunction(packs);

    return returnedState{1, value};
}

///home/sofia/CLionProjects/untitled4/Solver.cpp
int Solver::heuristicFunction(int card_ind, int pack_ind, const std::vector<Pack>& packs) {
    double topCards{0};
    for (auto& pack : packs) {
        topCards += (packs.head() - 6);
    }
    topCards /= 14.0;
    double way = 0.0;
    for (int i = 0; i < packs[pack_ind].size(); i++) {
        if (packs[pack_ind][i]->rank == all_cards[card_ind].rank - 1) {
            way += (8 - std::abs(pack_ind - i));
        }
    }
    way /= 8.0;
    return round((topCards + way) * 1000);
}