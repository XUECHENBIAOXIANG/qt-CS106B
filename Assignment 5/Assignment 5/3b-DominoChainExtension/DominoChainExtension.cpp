/*
 * File: DominoChainExtension.cpp
 * ----------------------------
 * Name: [TODO: enter name here]
 * This file is the starter code for Domino Chain Extension problem
 * from Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <cctype>
#include <string>
#include "domino.h"
#include "strlib.h"
#include "tokenscanner.h"
#include "vector.h"
#include "set.h"
#include "console.h"
using namespace std;

/* Function prototypes */

void testFormsALLDominoChains(string str);
Set<Vector<Domino>> formsALLDominoChains(Vector<Domino>& dominos);
Vector<Domino> createDominoVector(string str);
Set<Vector<Domino>> formsALLDominoChainsRec(Vector<Domino> &
                                                dominos,
                                            int start,
                                            const Vector<Domino> &
                                                dominoChain);
/* Main program */

int main() {
   testFormsALLDominoChains("1-4, 1-6, 2-6, 3-4, 4-4");
   testFormsALLDominoChains("1-6, 2-6, 3-4, 4-4");
   testFormsALLDominoChains("2-5, 3-6, 5-1, 3-5, 1-6");
   return 0;
}

void testFormsALLDominoChains(string str) {
   Vector<Domino> dominos = createDominoVector(str);
   Set<Vector<Domino>> dominoChainsSet = formsALLDominoChains(dominos);
   cout << boolalpha << endl << "Forms Domino Chain (" << str << ") -> "
        << (!dominoChainsSet.isEmpty() ? "Success!" : "Failure!") << endl;
   for(Vector<Domino> dominoChain : dominoChainsSet){
       cout<< " Begin -> ";
       for(Domino domino : dominoChain)
           cout << domino << "->";
       cout << " End" << endl;
   }
}

/*
 * Wrapper Function: formsALLDominoChains
 * Usage:  dominoChainsSet = formsALLDominoChains(dominos)
 */

Set<Vector<Domino>> formsALLDominoChains(Vector<Domino> & dominos){
    // TODO: Delete this line and the next two lines, then implement this function.
    return formsALLDominoChainsRec(dominos, -1, {});}
/*
 * TODO: designs and implements the recursive function that
 * forms all domino chains
 * ------------------------------------------------------------------------
 */
Set<Vector<Domino>> formsALLDominoChainsRec(Vector<Domino> &
                                                dominos,
                                            int start,
                                            const Vector<Domino> &
                                                dominoChain){
    if (dominos.isEmpty()) return {dominoChain};
    Set<Vector<Domino>> dominoChainsSet;
    for (int i = 0; i < dominos.size(); i++) {
        auto candidate = dominos[i];


            auto rest = dominos;
        rest.remove(i);
        auto extendedDominoChain = dominoChain;
        if (start == -1 || start == candidate.getLeftDots()) {
            dominoChainsSet += formsALLDominoChainsRec(rest,
                                                       candidate.getRightDots(),

                                                       extendedDominoChain += candidate);
        }
        extendedDominoChain = dominoChain;
        if (start == -1 || start == candidate.getRightDots()) {
            dominoChainsSet += formsALLDominoChainsRec(rest,
                                                       candidate.getLeftDots(),

                                                       extendedDominoChain += candidate.turnOver());
        }
    }
    return dominoChainsSet;
}


/*
 * Function: createDominoVector
 * Usage: Vector<Domino> vec = createDominoVector(str);
 * ----------------------------------------------------
 * Parses a string composed of comma-separated left-right pairs into a
 * chain of Domino objects.
 */

Vector<Domino> createDominoVector(string str) {
   Vector<Domino> vec;
   TokenScanner scanner(str);
   scanner.ignoreWhitespace();
   while (true) {
      int left = stringToInteger(scanner.nextToken());
      scanner.verifyToken("-");
      int right = stringToInteger(scanner.nextToken());
      vec += Domino(left, right);
      if (!scanner.hasMoreTokens()) break;
      scanner.verifyToken(",");
   }
   return vec;
}
