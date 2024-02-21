// card_list.h
// Author: Mihir Kondapalli
// All class declarations related to defining a BST that represents a player's hand

#ifndef CARD_LIST_H
#define CARD_LIST_H

#include "card.h"

class CardBST
{
    public:

        BST();
        void insert(Card* card);
        void getSuccessor(Card* card);
        void getPredecessor(Card* node)
        void remove(Card* card);
        ~BST();

    private:

        void insertHelper(Card* card, Node* start);
        void getSuccessorHelper(Card* card, Node* start);
        void getPredecessorHelper(Card* card, Node* start)
        void removeHelper(Card* card, Node* start);
        void clear(Node* root);

        struct Node
        {
            Card* card;
            Node* left;
            Node* right;
            Node* parent;

            Node(Card* inCard = nullptr): card(inCard), left(0), right(0), parent(0) {}
        };

        Node* head;
};

#endif
