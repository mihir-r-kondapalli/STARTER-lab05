// card_list.cpp
// Author: Mihir Kondapalli
// Implementation of the classes defined in card_list.h

#include "card_list.h"
#include <iostream>
using namespace std;

CardBST::CardBST()
{
    head = nullptr;
}

CardBST::~CardBST()
{
    clear(head);
}

void CardBST::clear(Node* root)
{
    if(root==nullptr)
    {
        return;
    }

    clear(root->left);
    clear(root->right);

    delete root;
}

void CardBST::insert(Card* card)
{
    if(head==nullptr)
    {
        head = new Node(card);
        return;
    }
    
    insertHelper(card, head);
}

void CardBST::insertHelper(Card* card, Node* root)
{   
    if(*card < *(root->card))
    {
        if(root->left == nullptr)
        {
            Node* temp = new Node(card);
            temp->parent = root;
            root->left = temp;
            return;
        }
        insertHelper(card, root->left);
        return;
    }
    
    if(*card > *(root->card))
    {   
        if(root->right == nullptr)
        {
            Node* temp = new Node(card);
            temp->parent = root;
            root->right = temp;
            return;
        }
        insertHelper(card, root->right);
        return;
    }
    
    return;
}

bool CardBST::contains(Card* card)
{
    if(card==nullptr)
    {
        return false;
    }
    
    return containsHelper(card, head);
}

bool CardBST::containsHelper(Card* card, Node* root)
{
    if(root == nullptr || root->card == nullptr){return false;}
    if(*card == *(root->card)){return true;}

    if(*(card) < *(root->card))
    {
        return containsHelper(card, root->left);
    }
    
    return containsHelper(card, root->right);
}

Card* CardBST::getMin()
{
    if(head==nullptr)
    {
        return nullptr;
    }

    return getMinHelper(head);
}

Card* CardBST::getMinHelper(Node* root)
{
    if(root->left==nullptr)
    {
        return root->card;
    }

    return getMinHelper(root->left);
}

Card* CardBST::getMax()
{
    if(head==nullptr)
    {
        return nullptr;
    }

    return getMaxHelper(head);
}

Card* CardBST::getMaxHelper(Node* root)
{
    if(root->right==nullptr)
    {
        return root->card;
    }

    return getMaxHelper(root->right);
}

CardBST::Node* CardBST::getNodeFor(Card* card, Node* root)
{
    if(root==nullptr){ return nullptr; }
    if(*card < *(root->card)){ return getNodeFor(card, root->left); }
    if(*card > *(root->card)){ return getNodeFor(card, root->right); }
    return root;
}

Card* CardBST::getPredecessor(Card* card)
{
    Node* temp = getPredecessorHelper(card, head);

    if(temp==nullptr)
    {
        return nullptr;
    }

    return temp->card;
}

CardBST::Node* CardBST::getPredecessorHelper(Card* card, Node* root)
{
    Node* temp = getNodeFor(card, head);
    if(temp==nullptr){return nullptr;}

    if(temp->left!=nullptr){
        temp = temp->left;
        while(temp->right!=nullptr){
            temp = temp->right;
        }
        return temp;
    }

    if(temp->parent!=nullptr){
        if(*(temp->parent->card) < *(temp->card)){
            return temp->parent;
        }
        if(*(temp->parent->card) > *(temp->card)){
            temp = temp->parent;
            while(temp->parent!=nullptr){
                if(*(temp->card) < *card){
                    return temp;
                }
                temp = temp->parent;
            }
            if(*(temp->card) < *(card)){
                    return temp;
            }
            
            return nullptr;
        }
    }

    return nullptr;
}

Card* CardBST::getSuccessor(Card* card)
{
    Node* temp = getSuccessorHelper(card, head);

    if(temp==nullptr)
    {
        return nullptr;
    }

    return temp->card;
}

CardBST::Node* CardBST::getSuccessorHelper(Card* card, Node* root)
{
    Node* temp = getNodeFor(card, head);
    if(temp==nullptr){return nullptr;}

    if(temp->right!=nullptr){
        temp = temp->right;
        while(temp->left!=nullptr){
            temp = temp->left;
        }
        return temp;
    }
    else
    {
        
        while(temp->parent != nullptr && (*(temp->parent->card) < *(temp->card)))
        {
            temp = temp->parent;
        }

        temp = temp->parent;

        return temp;
    }

    return nullptr;
}

int CardBST::getHeight()
{
    return getHeightHelper(head);
}

int CardBST::getHeightHelper(Node* root)
{
    if(root==nullptr)
    {
        return 0;
    }

    int lh = getHeightHelper(root->left);
    int rh = getHeightHelper(root->right);

    if(lh>rh)
    {
        return 1+lh;
    }
    
    return 1+rh;
}

bool CardBST::remove(Card* card)
{
    Node* n = getNodeFor(card, head);

    return removeHelper(n, head);
}

bool CardBST::removeHelper(Node* c, Node* root)
{
    Node* temp = c;

    if(temp == nullptr)
    {
        return false;
    }

    if(temp->left == nullptr && temp->right == nullptr)
    {
        
        if(temp->parent == nullptr)
        {
            root = nullptr;
        }
        else if(temp->parent->left == temp)
        {
            temp->parent->left = nullptr;
        }
        else if(temp->parent->right == temp)
        {
            temp->parent->right = nullptr;
        }

        delete temp;
        return true;
    }

    if(temp->left == nullptr)
    {

        if(temp->parent == nullptr)
        {
            head = temp->right;
            head->parent = nullptr;
        }
        else if(temp->parent->left == temp)
        {
            temp->parent->left = temp->right;
            temp->right->parent = temp->parent;
        }
        else if(temp->parent->right == temp)
        {
            temp->parent->right = temp->right;
            temp->right->parent = temp->parent;
        }

        delete temp;
        return true;
    }

    if(temp->right == nullptr)
    {
        
        if(temp->parent == nullptr)
        {
            head = temp->left;
            head->parent = nullptr;
        }
        else if(temp->parent->left == temp)
        {
            temp->parent->left = temp->left;
            temp->left->parent = temp->parent;
        }
        else if(temp->parent->right == temp)
        {
            temp->parent->right = temp->left;
            temp->left->parent = temp->parent;
        }

        delete temp;
        return true;
    }

    Node* next = getSuccessorHelper(temp->card, head);

    // The error that took me forever to find and fix (not dereferencing the pointers here)
    *(temp->card) = *(next->card);

    if(next->parent == temp)
    {
        next->parent->right = next->right;
        if(next->right != nullptr)
        {
            next->right->parent = next->parent;
        }
    }
    else
    {
        next->parent->left = next->right;
        if(next->right != nullptr)
        {
            next->right->parent = next->parent;
        }
    }

    delete next;
    return true;
}

void CardBST::check_node(Node* n)
{
    int suite = n->card->getSuite();
    int val = n->card->getVal();

    int num_children = (n->left!=nullptr) + (n->right!=nullptr);
    int parent = (n->parent != nullptr);
    
    cout << suite << " " << val << ": " << num_children << " " << parent << endl;
}

void CardBST::printBST()
{
    printInOrderBSTHelper(head);
}

void CardBST::printInOrderBSTHelper(Node* root)
{
    if(root==nullptr)
    {
        return;
    }

    printInOrderBSTHelper(root->left);
    cout << root->card->toString() << endl;
    printInOrderBSTHelper(root->right);
}

void CardBST::printPreBST()
{
    printPreOrderBSTHelper(head);
}

void CardBST::printPreOrderBSTHelper(Node* root)
{
    if(root==nullptr)
    {
        return;
    }

    check_node(root);
    cout << root->card->toString() << endl;
    printPreOrderBSTHelper(root->left);
    printPreOrderBSTHelper(root->right);
}