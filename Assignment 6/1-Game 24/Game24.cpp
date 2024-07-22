/*
 * File: Game 24.cpp
 * ----------------------------
 * Name: [TODO: enter name here]
 * This file is the starter code for the Game 24 problem
 * from Assignment #4.
 * [TODO: extend the documentation]
 */

#include <string>
#include "console.h"
#include "error.h"
#include "simpio.h"
#include "tokenscanner.h"
#include "vector.h"
#include "set.h"
#include "strlib.h"
#include "card.h"
#include "display.h"

using namespace std;

/* Constants */
const int BIGNUM = 24;

Set<string> countTwentyFours(Vector<Card> & cards);

bool counts(Vector<Card> & cards, int n, Set<string> & ans);

int main(){
    initGraphics("GAME 24");
    while (true){
        // string handCardsString = "5C 10S 4H 9C";
        string handCardsString = getLine("Please input a hand of Cards:");
        if (handCardsString == "") break;
        TokenScanner scanner(handCardsString);
        scanner.ignoreWhitespace();
        Vector<Card> cards;
        bool isLegalCard = true;
        while (scanner.hasMoreTokens()) {
            string tokenString = scanner.nextToken();
            Card handCard = Card(tokenString);
            if(!handCard.fail())
               cards.add(handCard);
            else
               isLegalCard = false;
        }
        int cardsNum = cards.size();
        if (isLegalCard && cardsNum > 1 && cardsNum < 7){
            Set<string> solutionsStrings = countTwentyFours(cards);
            displayHandCards(handCardsString, cardsNum);
            displaySolutions(solutionsStrings, cardsNum);
        }
        else
            cout << "Please give at least 2 cards, up to 6 cards!" << endl << endl;
    }
    cout<<endl<<"Game Over and the windows will be closed in a few seconds..."<<endl;
    pause(3000);
    closeGraphics();
    return 0;
}
bool counts(Vector<Card> & cards, int n, Set<string> & ans)
{
    if(n == 1)
    {
        if(cards[0] == BIGNUM)
        {
            ans += cards[0].toExpressionString();
            return true;
        }
        else return false;
    }
    else
    {
        bool flag = false;
        for(int i = 0; i < n; i++)
        {
            Card tmp1 = cards[i];
            for(int j = i+1; j < n; j++)
            {
                Card tmp2 = cards[j];
                Vector<Card> result;
                result.add(tmp1 + tmp2);
                result.add(tmp1 * tmp2);
                if(tmp1.getRank() - tmp2.getRank() >= 0) {result.add(tmp1 - tmp2);}
                else{ result.add(tmp2 - tmp1);}
                if(tmp1 != 0 && tmp2 !=0)
                {
                    result.add(tmp1 / tmp2);
                    if(tmp1 != tmp2) {result.add(tmp2 / tmp1);}
                }
                for(Card m : result)
                {
                    cards[i] = m;
                    cards[j] = cards[n - 1];
                    if(counts(cards, n - 1, ans)) flag = true;
                    cards[i] = tmp1;
                    cards[j] = tmp2;
                }
            }
        }
        return flag;
    }
}

Set<string> countTwentyFours(Vector<Card> & cards){
    //   TODO: modify the code and implement the recursive strategy.
    Set<string> solutionsStrings = {};
    counts(cards, cards.size(), solutionsStrings);
    return solutionsStrings;
}






