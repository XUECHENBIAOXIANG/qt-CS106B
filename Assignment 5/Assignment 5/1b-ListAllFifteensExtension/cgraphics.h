#ifndef CGRAPHICS_H
#define CGRAPHICS_H

#include <string>
#include "card.h"
#include "vector.h"

using namespace std;

/* Global variables */

const int Y_START = 100;
const int ROW_HEIGHT = 100;
const int MAXWIDTH = 1000;
const int MAXHEIGHT = 800;

/* Function prototypes */

void initGraphics(string title = "List All Fifteens", int width = MAXWIDTH, int height = MAXHEIGHT);
void closeGraphics();
void displayResult(const Vector<Card> & cards, const Vector<Vector<Card>>& setCards);
void displayCards(const Vector<Card> & cards, int xStart, int yStart, int columnWidth);


#endif // CGRAPHICS_H
