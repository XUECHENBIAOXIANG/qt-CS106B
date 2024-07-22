/*
 * File: main.cpp
 * --------------
 * Blank C++ project configured to use Stanford cslib and Qt
 */

#include "console.h"
#include "simpio.h"
#include "gwindow.h"
#include "gcolor.h"
#include <string>
using namespace std;


int main()
{
    string name = getLine("What is your name?");
    cout << "Hello, " << name << endl;
    static GWindow *gw = nullptr;
    if((gw = new GWindow(100, 100)))
    {
        static int offset = 0;
        offset += 30;
        gw->setLocation(0, 0);
        gw->setBackground(GColor::convertRGBToRGB(18,92,39));
        gw->setColor("Black");
        gw->clear();
        gw->setTitle("title");
        gw->setVisible(true);
        gw->requestFocus();
    }
    else{
        cout << "Initialize Graphics Interface Failed!" << endl;
        exit(1);
    }
    return 0;
}
