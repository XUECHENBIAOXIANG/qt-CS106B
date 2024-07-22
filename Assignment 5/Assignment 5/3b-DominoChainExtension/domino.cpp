#include "domino.h"

Domino::Domino(int left, int right){
    leftDots = left;
    rightDots = right;
}

int Domino::getLeftDots() const{
    return leftDots;
}

int Domino::getRightDots() const{
    return rightDots;
}

Domino Domino::turnOver(){
    return Domino(this->rightDots, this->leftDots);
}

bool Domino::operator>(const Domino &domino) const{
    return this->leftDots > domino.leftDots;
}

bool Domino::operator<(const Domino &domino) const{
    return this->leftDots < domino.leftDots;
}

bool Domino::operator==(const Domino &domino) const{
    return this->leftDots == domino.leftDots;
}

ostream & operator<<(ostream &os, const Domino &domino){
    os << "(" << domino.leftDots << "-" << domino.rightDots << ")";
    return os ;
}

