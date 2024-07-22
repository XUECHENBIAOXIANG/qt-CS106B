/*
 * File: StockCutting.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * This file is the starter code for the stock-cutting problem
 * fron Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "console.h"
#include "vector.h"
using namespace std;

/* Function prototypes */
void testCutStock(Vector<int> & requests, int stockLength);
int cutStock(Vector<int> & requests, int stockLength);
int cutWithRemnants(Vector<int> requests, Vector<int> remnants, int
                                                                    stockLen);
/* Main program */

int main() {
   Vector<int> test1;
   test1 += 4, 3, 4, 1, 7, 8;
   testCutStock(test1, 10);
   Vector<int> test2;
   test2 += 6, 6, 3, 3, 2, 2, 2, 2, 2;
   testCutStock(test2, 10);
   return 0;
}

/*
 * Function: cutStock
 * Usage: int units = cutStock(requests, stockLength);
 * ---------------------------------------------------
 * Computes the minimum number of stock pipes required to satisfy
 * the vector of requests of individual pieces.
 */

int cutStock(Vector<int> & requests, int stockLength) {
   // TODO: Delete this line and the next three lines, then implement this function.
    return cutWithRemnants(requests, {}, stockLength);

}

/*
 * TODO: Designs and implements the recursive function that
 * computes the minimum number of stock pipes required to satisfy
 * the vector of requests of individual pieces
 * ------------------------------------------------------------------------
 */
int cutWithRemnants(Vector<int> requests, Vector<int> remnants, int
                                                                    stockLen) {
    if (requests.isEmpty()) return 0;
    int min = requests.size();
    int request = requests[0];
    requests.remove(0);
    for (int i = 0; i < remnants.size(); i++) {
        if (remnants[i] >= request) {
            remnants[i] -= request;
            int cur = cutWithRemnants(requests, remnants, stockLen);
            if (cur < min) min = cur;
            remnants[i] += request;
        }
    }
    remnants.add(stockLen - request);
    int cur = 1 + cutWithRemnants(requests, remnants, stockLen);
    if (cur < min) min = cur;
    return min;
}

/*
 * Function: testCutStock
 * Usage: testCutStock(requests, stockLength);
 * -------------------------------------------
 * Conducts a test of the cutStock implementation by reporting how many
 * units are required to satisfy the requests.
 */

void testCutStock(Vector<int> & requests, int stockLength) {
   cout << "cutStock([";
   for (int i = 0; i < requests.size(); i++) {
      if (i > 0) cout << ", ";
      cout << requests[i];
   }
   cout << "]) -> " << cutStock(requests, stockLength) << endl;
}
