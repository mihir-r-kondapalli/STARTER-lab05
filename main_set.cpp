// Feb 14: This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"

using namespace std;


// Picks first matching card between the sets in ascending order if
// turn is false and vice versa
string get_first(set<Card> &set1, set<Card> &set2, bool turn)
{ 
  // Alice's turn
  if(!turn)
  {
    set<Card>::iterator itr1;
    set<Card>::iterator itr2;

    for (itr1 = set1.begin(); itr1 != set1.end(); itr1++) 
    {
      itr2 = set2.find(*itr1);
      
      if(itr2!=set2.end())
      {
        set2.erase(*itr2);
        string s = (*itr1).toString();
        set1.erase(itr1);
        return s;
      }
    }

    // No matching cards
    return "";
  }
  else
  {
    set<Card>::reverse_iterator itr1;
    set<Card>::iterator itr2;

    // If it's Bob's turn
    for (itr1 = set2.rbegin(); itr1 != set2.rend(); itr1++) 
    {
      itr2 = set1.find(*itr1);
      
      if(itr2!=set1.end())
      {
        set1.erase(itr2);
        string s = (*itr1).toString();
        set2.erase(*itr1);
        return s;
      }
    }

    // No matching cards
    return "";
  }

  return "";
}


void run_game(set<Card> &alice_cards, set<Card> &bob_cards)
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

  set<Card>::iterator itr;
  for(itr = alice_cards.begin(); itr != alice_cards.end(); itr++) 
  {
    cout << (*itr).toString() << endl;
  }

  cout << endl;
  cout << "Bob's cards:" << endl;

  for(itr = bob_cards.begin(); itr != bob_cards.end(); itr++) 
  {
    cout << (*itr).toString() << endl;
  }
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

  Card* card;

  set<Card> alice_cards;

  //Read each file
  while (getline (cardFile1, line) && (line.length() > 0)){
    card = new Card(line);
    alice_cards.insert(*card);
  }
  cardFile1.close();

  set<Card> bob_cards;

  while (getline (cardFile2, line) && (line.length() > 0)){
    card = new Card(line);
    bob_cards.insert(*card);
  }
  cardFile2.close();
  
  run_game(alice_cards, bob_cards);

  return 0;
}