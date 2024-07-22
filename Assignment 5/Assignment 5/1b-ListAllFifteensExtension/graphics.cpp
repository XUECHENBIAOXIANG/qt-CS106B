#include "cgraphics.h"
#include "gwindow.h"
#include "gcolor.h"
#include <string>

#ifdef _WIN32
static const string RESOURCEDIRECTORY = "res\\";
#elif
static const string RESOURCEDIRECTORY = "res/";
#endif

/* Global variables */
static GWindow *gw = nullptr;

void initGraphics(string title, int width, int height)
{
    if((gw = new GWindow(width, height)))
    {
        static int offset = 0;
        offset += 30;
        gw->setLocation(450 + offset, 100 + offset);
        gw->setBackground(GColor::convertRGBToRGB(18,92,39));
        gw->clear();
        gw->setTitle(title);
        gw->setVisible(true);
        gw->requestFocus();
    }
    else{
        cout << "Initialize Graphics Interface Failed!" << endl;
        exit(1);
    }
}

void closeGraphics()
{
    if (gw)
       delete gw;
}

void displayCards(const Vector<Card> & cards, int xStart, int yStart, int columnWidth)
{
    int temp = xStart;
    for(int i = cards.size(); i>0 ; i--)
    {
        gw->drawImage(RESOURCEDIRECTORY + "Back.gif", xStart, yStart);
        xStart += columnWidth ;
        pause(200);
    }

    pause(500);

    xStart = temp;
    for(Card c : cards)
    {
        gw->drawImage(RESOURCEDIRECTORY + c.toString() + ".gif", xStart, yStart);
        xStart += columnWidth ;
        pause(200);
    }
}

void displayResult(const Vector<Card> & cards, const Vector<Vector<Card>>& setCards)
{
    displayCards(cards, 50, 50, 120);
    int yStart = Y_START;
    for(const Vector<Card>& cards : setCards)
    {
       displayCards(cards, 50, yStart+=ROW_HEIGHT, 120);
    }
    pause(5000);
}

