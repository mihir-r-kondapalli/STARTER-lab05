// Feb 14: This file should implement the game using a custom implementation of a BST (that is based on your implementation from lab02)
#include <iostream>
#include <fstream>
#include <string>
#include "card.h"
#include "card_list.h"
#include <vector>
//Do not include set in this file

using namespace std;


// Picks first matching card between the sets in ascending order if
// turn is false and vice versa
string get_first(CardBST& alice_cards, CardBST& bob_cards, bool turn)
{

  // Alice's turn
  if(!turn)
  {
    Card* temp = alice_cards.getMin();

    while(temp!=nullptr)
    {
      if(bob_cards.contains(temp))
      {
        string s = temp->toString();
        bob_cards.remove(temp);
        alice_cards.remove(temp);
        return s;
      }

      temp = alice_cards.getSuccessor(temp);
    }

    // No matching cards
    return "";
  }
  else
  {
    // Bob's turn
    Card* temp = bob_cards.getMax();

    while(temp!=nullptr)
    {
      if(alice_cards.contains(temp))
      {
        string s = temp->toString();
        alice_cards.remove(temp);
        bob_cards.remove(temp);
        return s;
      }

      temp = bob_cards.getPredecessor(temp);
    }

    // No matching cards
    return "";
  }

  return "";
}

void run_game(CardBST& alice_cards, CardBST& bob_cards)
{ 
  bool end = false;
  bool turn = false; // false for alice, true for bob
  
  string cmessage;

  while(!end)
  {
    cmessage = get_first(alice_cards, bob_cards, turn);
    if(cmessage == "")
    {
      end = true;
    }
    else
    {
      if(!turn)
      {
        cout << "Alice picked matching card " << cmessage << endl;
      }
      else
      {
        cout << "Bob picked matching card " << cmessage << endl;
      }
    }

    turn  = !turn;
  }

  cout << endl;
  cout << "Alice's cards:" << endl;

  alice_cards.printBST();

  cout << endl;
  cout << "Bob's cards:" << endl;

  bob_cards.printBST();
}


int main(int argv, char** argc){
  
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }

  CardBST alice_cards;
  CardBST bob_cards;

  //Read each file
  while (getline (cardFile1, line) && (line.length() > 0)){
    Card* card = new Card(line);
    alice_cards.insert(card);
  }
  cardFile1.close();


  while (getline (cardFile2, line) && (line.length() > 0)){
    Card* card = new Card(line);
    bob_cards.insert(card);
  }
  cardFile2.close();
  
  run_game(alice_cards, bob_cards);

  return 0;
}
