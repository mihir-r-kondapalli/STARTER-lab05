// card.cpp
// Author: Mihir Kondapalli
// Implementation of the classes defined in card.h

#include "card.h"
#include <string>
#include <iostream>
using namespace std;

// Constructor with suite and val parameters
// If val is 10, then v is 't'
Card::Card(char s, char v)
{
    if(v == 'a'){val = 1;}
    else if(v == 't'){val = 10;}
    else if(v == 'j'){val = 11;}
    else if(v == 'q'){val = 12;}
    else if(v == 'k'){val = 13;}
    else{val = v-'0';}

    if(s == 'c'){suite = 1;}
    else if(s == 'd'){suite = 2;}
    else if(s == 's'){suite = 3;}
    else{suite = 4;}
}

Card::Card(string cardInfo)
{
    
    char s = cardInfo.at(0);
    char v = ' ';
    if(cardInfo.size()==3)
    {
        v = cardInfo.at(2);
    }
    if(cardInfo.size()==4)
    {
        v = 't';
    }

    if(v == 'a'){val = 1;}
    else if(v == 't'){val = 10;}
    else if(v == 'j'){val = 11;}
    else if(v == 'q'){val = 12;}
    else if(v == 'k'){val = 13;}
    else{val = v-'0';}

    if(s == 'c'){suite = 1;}
    else if(s == 'd'){suite = 2;}
    else if(s == 's'){suite = 3;}
    else{suite = 4;}
}

int Card::getSuite() const
{
    return suite;
}

int Card::getVal() const
{
    return val;
}

// If greater in suite, return 2
// If equal in suite but greater in value, return 1
// If equal in suite and value, return 0
// If equal in suite, but lesser in value, return -1
// If lesser in suite, return -2
int Card::compare(const Card& card) const
{
    if(suite > card.getSuite())
    {
        return 2;
    }

    if(suite < card.getSuite())
    {
        return -2;
    }

    if(val > card.getVal())
    {
        return 1;
    }

    if(val < card.getVal())
    {
        return -1;
    }

    return 0;
}

void Card::operator=(const Card& card)
{
    suite = card.getSuite();
    val = card.getVal();
}

bool Card::operator>(const Card& card) const
{
    return compare(card) > 0;
}

bool Card::operator<(const Card& card) const
{
    return compare(card) < 0;
}

bool Card::operator==(const Card& card) const
{
    return compare(card) == 0;
}

string Card::toString() const
{
    char s; char v;

    if(suite == 1){s='c';}
    else if(suite == 2){s='d';}
    else if(suite == 3){s='s';}
    else{s = 'h';}

    if(val == 1){v='a';}
    else if(val == 10){v='t';}
    else if(val == 11){v='j';}
    else if(val == 12){v='q';}
    else if(val == 13){v='k';}
    else{v = (char)(val+'0');}
    
    string empty = "";
    empty+=s;
    empty+=" ";
    if(v=='t'){empty+="10";}
    else{empty+=v;}

    return empty;
}

Card::~Card(){}