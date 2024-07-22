/*
 * File: NumericConversion.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * This file is the starter project for the numeric-conversion problem
 * in which you implement the functions intToString and stringToInt from
 * Assignment #3
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
#include <string>
#include <cctype>
using namespace std;

/* Function prototypes */
string integerToString(int n);
int stringToInteger(string str);
bool isNumeric(string &str);

/* Main program */
int main()
{
    int N = getInteger("Please input integer N: ");
    cout<<"Converted String is:"<<integerToString(N)<<endl<<endl;
    string str;
    do{
        str = getLine("Please input a digital string: ");
        if(isNumeric(str))
            break;
        else
            cout<<"Illeagal digital string format. Try again!"<<endl<<endl;
    } while(true);

    cout<<"Converted Integer is:"<<stringToInteger(str)<<endl;
    return 0;
}

/*
 * Function: integerToString
 * Usage: str = integerToString(n);
 * ------------------------
 * This function performs converting a integer to a string.
 */
string integerToString(int n)
{
    // TODO: Delete this line and the next two lines, then implement this function.
    if(n<0)
        return "-" + integerToString(-n);
    if(n<10)
        return char(n + '0') + string();
    return integerToString(n / 10) + char(n % 10 + '0') + string();
}

/*
 * Function: stringToInteger
 * Usage: n = stringToInteger(str);
 * ------------------------
 * This function performs converting a string to a integer.
 */
int stringToInteger(string str)
{
    // TODO: Delete this line and the next two lines, then implement this function.
    if(str[0] == '-')
        return -stringToInteger(str.substr(1));
    if(str.length() == 1)
        return str[0] - '0';
    return str[str.length()-1] - '0' + 10 *
                                             stringToInteger(str.substr(0,str.length()-1));

}

/*
 * Function: isNumeric
 * Usage: bool flag = isNumeric(str);
 * ------------------------
 * This function checks a legal digital string.
 */
bool isNumeric(string &str)
{
    if(!str.length())
        return false;
    unsigned int startPosition = 0;
    if(str[0] == '-'){
        if(str.length()==1){
            return false;
        }
        else{
            startPosition = 1;
        }
    }
    for(unsigned int i = startPosition; i<str.length();i++)
        if(isdigit(str[i]))
            ;
        else
            return false;
    return true;
}

