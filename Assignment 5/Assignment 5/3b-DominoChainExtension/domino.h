#ifndef DOMINO_H
#define DOMINO_H
#include <iostream>
using namespace std;

class Domino
{
    int leftDots;
    int rightDots;
public:
    Domino(){}
    Domino(int left, int right);
    Domino turnOver();
    int getLeftDots() const;
    int getRightDots() const;
    bool operator>(const Domino &domino) const;
    bool operator<(const Domino &domino) const;
    bool operator==(const Domino &domino) const;
    friend ostream & operator<<(ostream &os, const Domino &domino);
};

#endif // DOMINO_H
