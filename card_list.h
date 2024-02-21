// card_list.h
// Author: Mihir Kondapalli
// All class declarations related to defining a BST that represents a player's hand

#ifndef CARD_LIST_H
#define CARD_LIST_H

#include "card.h"
#include <vector>

class CardBST
{
    public:

        CardBST();
        void insert(Card* card);
        bool contains(Card* card);
        Card* getMin();
        Card* getMax();
        Card* getPredecessor(Card* card);
        Card* getSuccessor(Card* card);
        void remove(Card* card);
        void printBST();
        ~CardBST();

    private:

        struct Node
        {
            Card* card;
            Node* left;
            Node* right;
            Node* parent;

            Node(Card* inCard = nullptr): card(inCard), left(0), right(0), parent(0) {}
            ~Node() {delete card;}
        };

        Node* head;

        void insertHelper(Card* card, Node* start);
        bool containsHelper(Card* card, Node* start);
        Card* getMinHelper(Node* root);
        Card* getMaxHelper(Node* root);
        Node* getNodeFor(Card* card, Node* start);
        Node* getPredecessorHelper(Card* card, Node* start);
        Node* getSuccessorHelper(Card* card, Node* start);
        void removeHelper(Card* card, Node* start);
        void clear(Node* start);
        void printInOrderBSTHelper(Node* start);
};

#endif
