// card.h
// Author: Mihir Kondapalli
// All class declarations related to defining a single card go here

#ifndef CARD_H
#define CARD_H

#include <string>
using namespace std;

class Card
{
    public:
        Card(char s, char v);
        Card(string cardInfo);
        int getSuite() const;
        int getVal() const;
        int compare(const Card& card) const;
        bool operator>(const Card & card) const;
        bool operator<(const Card & card) const;
        bool operator==(const Card & card) const;
        string toString() const;
        ~Card();

    private:
        int suite; // clubs is 1, diamonds is 2, spades is 3, hearts is 4
        int val; // ace is 1, jack is 11, queen is 12, king is 13, rest is the same
};

#endif
