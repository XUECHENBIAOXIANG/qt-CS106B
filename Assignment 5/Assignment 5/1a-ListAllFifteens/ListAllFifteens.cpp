/*
 * File: CountFifteens.cpp
 * -----------------------
 * Name: [TODO: enter name here]
 * This file is the starter code for the CountFifteens problem from
 * Assignment #3.
 * [TODO: extend the documentation]
 */

#include <exception>
#include <iostream>
#include <string>
#include "card.h"
#include "console.h"
#include "simpio.h"
#include "tokenscanner.h"
#include "vector.h"
using namespace std;

/* Function prototypes */

int listAllFifteens(Vector<Card> & cards);
// TODO: declare the recursive function listAllFifteensRec
int listAllFifteensRec(Vector<Card> & cards, int start, int target);
/* Main program */

int main() {
   while (true) {
      string line = getLine("Enter a hand of cards: ");
      if (line == "") break;
      TokenScanner scanner(line);
      scanner.ignoreWhitespace();
      Vector<Card> hand;
      while (scanner.hasMoreTokens()) {
         hand.add(Card(scanner.nextToken()));
      }
      int nWays = listAllFifteens(hand);
      string plural = (nWays == 1) ? "" : "s";
      cout << nWays << " way" << plural << endl;
   }
   return 0;
}

/*
 * Counts the number of ways of making a total of 15 from the vector of
 * cards.
 */

int listAllFifteens(Vector<Card> & cards) {
    // TODO: Delete this line and the next two lines, then implement this wrapper function.
    return listAllFifteensRec(cards, 0, 15);

}
int listAllFifteensRec(Vector<Card> & cards, int start, int target){
    if (start == cards.size()) {
        return (target == 0) ? 1 : 0;
    }
    if (target < 0) return 0;
    int cRank = cards[start].getRank();
    if (cRank > 10) cRank = 10;
    return listAllFifteensRec(cards, start + 1, target)
           + listAllFifteensRec(cards, start + 1, target - cRank);
}
   // TODO: Implement the recursive function listAllFifteensRec.
