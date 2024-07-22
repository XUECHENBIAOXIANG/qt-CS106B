/*
 * File: Boggle.cpp
 * -----------------------
 * Name: [TODO: enter name here]
 * This file is the starter code for the Boggle Game problem
 * from Assignment #4.
 * [TODO: extend the documentation]
 */

#include <cctype>
#include <fstream>
#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "vector.h"
#include "console.h"
#include "strlib.h"
#include "simpio.h"
#include<set>
//#include <QMediaPlayer>
#include "console.h"

using namespace std;

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;
const string STANDARD_CUBES_FIlE = "cubes16.txt";
const string BIG_BOGGLE_CUBES_FILE = "cubes25.txt";
const int Bordsize = 4;
char allletter[4][4];
Lexicon dictionary("res/EnglishWords.txt");
//stanford定义的字符串
string StandardCubes[16]  =
    {"AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS", "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
     "DISTTY", "EEGHNW", "EEINSU", "EHRTVW", "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"};

/* Function prototypes */

void welcome();
void giveInstructions();
void playBoggle();

/* Main program */

// You need to design specific data structures and functions
// to complete this assignment.

int main() {

    welcome();
    if (getYesOrNo("Do you need instructions? ")) {
       giveInstructions();
    }

   playBoggle();
   return 0;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
   cout << "Welcome!  You're about to play an intense game ";
   cout << "of mind-numbing Boggle.  The good news is that ";
   cout << "you might improve your vocabulary a bit.  The ";
   cout << "bad news is that you're probably going to lose ";
   cout << "miserably to this little dictionary-toting hunk ";
   cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

void computerTurn(const Set<string>& s) {
    for (const auto& elem : s) {
        recordWordForPlayer(elem,COMPUTER);
    }
}


void printSet(const Set<string>& s) {
    for (const auto& elem : s) {
        cout << elem << endl;
    }
}

//游戏开始
void StartGame(){
    // Grid<string> board = BoardSetup();  //得到board
    // DrawBoard(board);
    setupGame();
    Set<string> allsolutions = getallsolution();//找出所有可能的单词
    cout << "-- It's your turn!!!\n"<<endl;
    // printset(playersoltuion);
    // printSet(allsolutions);
    Set<string> playersoltuion = PlayerTurn(allsolutions);

    Set<string> computersolution = allsolutions;
        cout << "-- It's computer turn!!!\n"<<endl;
    computerTurn(computersolution);
    // cout << "-- The computer's sollution is :\n"<<endl;
    // printset(computersolution);

    ofstream outf;
    ifstream inf;
    // inf.open("./res/cubes16.txt");          //特别注意，这里是：//  是双斜杠喔~~


}

void setupGame(){
    int boardSize = Bordsize;  //设定board大小
    int dimension = 4;
    Vector<string> cube;
    cube = StringArrayToVector(StandardCubes, boardSize);//获取填充用的vector

    // shuffle(StandardCubes, 16);
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            char temp = stringToChar(toLowerCase(charToString(StandardCubes[r * dimension + c][randomInteger(0, 5)])));
            labelCube(r,c,temp);
            allletter[r][c]=temp;
            // gameBoard[r][c] = stringToChar(toLowerCase(charToString(CUBES[r * dimension + c][randomInteger(0, 5)])));
        }
    }
}

//board二维数组的建立部分//
Vector<string> StringArrayToVector(string arr[], int boardSize)
{
    Vector<string> vec;
    int size = boardSize * boardSize;
    for (int i = 0; i < size; i++)
    {
        vec.add(arr[i]);
    }
    return vec;
}



//递归函数
void FindCompWords( int row, int col,
                   string soFar, Set<string> & allsoultions)
{

    char letter = allletter[row][col]; // 取出单词
    string current = soFar + letter; // 加入current
    // 如果找到单词结束递归
    if (current.length() >= 4 && dictionary.contains(current))
    {
        if(!(allsoultions.contains(current))){
            string temp = toLowerCase(current);
            allsoultions.add(temp);
        }
        return;
    }
    // 如果不含前缀结束递归
    if (!dictionary.containsPrefix(soFar))
    {
        return;
    }
    // 递归结构：条件{  标记； 递归； 解除标记；}
    for (int vert = -1; vert <= 1; vert++)
    {
        for (int horiz = -1; horiz <= 1; horiz++)
        {
            // 递归条件：不超过边界 && 没被标记 && 不同时为0（本身）
            if (row + vert >= 0 && row + vert < 4 &&
                col + horiz >= 0 && col + horiz < 4 &&
                allletter[row + vert][col + horiz]!= '~'
                // getLetter(row + vert, col + horiz) != '~'
                &&!(horiz == 0 && vert == 0))
            {
                allletter[row][col] = '~';
                // board.setAt(row,col,"~"); //  标记
                FindCompWords(row+vert,col+horiz,current,allsoultions);//递归
                allletter[row][col]= letter;
                // board.setAt(row,col,letter); // 递归结束后取消标记
            }
        }
    }
}
//递归主函数
Set<string> getallsolution(){
    int boardSize = 4;
    Set<string> allsolutions;
    //设定递归传入参量：首字母的行列，初始量soFar, 判别量allsolution
    for (int row = 0; row < boardSize; row++)
    {
        for (int col = 0; col < boardSize; col++)
        {
            string soFar = "";
            FindCompWords(row,col,soFar,allsolutions);
        }
    }
    return allsolutions;
}
//
    void ParseGuess(string word, Set<string> &guesses,Set<string> & allsolutions )
{

    if (guesses.contains(word))//判断是否录过该单词
    {
        cout << "You've already guessed that word!" << endl;
        return;
    }
    if (word.length() < 4)
    {
        cout << "Not a valid word!" << endl;
        return;
    }
    // 找到单词
    bool haveword = false;
    if(allsolutions.contains(word)){
        guesses.add(word);
        allsolutions.remove(word);
        haveword = true;
        recordWordForPlayer(word,HUMAN);
    }
    if(!haveword)
        cout << "Couldn't find word on board." << endl;
}

//返回用户输入的得到的正确单词组
Set<string> PlayerTurn(Set<string> & allsolutions){
    Set<string> guesses;
    string word;
    while(true)
    {
        cout << endl << "Enter a word(enter a blank to finish): ";
        word = getLine();
        word = toLowerCase(word);
        if (word == "") break;
        ParseGuess(word, guesses, allsolutions);
    }
    return guesses;
}


//打印成绩和单词
void printset(Set<string> set){
    int score =0;
    int i = 0;
    cout <<endl;
    cout <<"\nthe scores are : "<<score<<endl;
    cout << "---------------------------------------------------------"<<endl;

}













/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
   cout << endl;
   cout << "The boggle board is a grid onto which I ";
   cout << "I will randomly distribute cubes. These ";
   cout << "6-sided cubes have letters rather than ";
   cout << "numbers on the faces, creating a grid of ";
   cout << "letters on which you try to form words. ";
   cout << "You go first, entering all the words you can ";
   cout << "find that are formed by tracing adjoining ";
   cout << "letters. Two letters adjoin if they are next ";
   cout << "to each other horizontally, vertically, or ";
   cout << "diagonally. A letter can only be used once ";
   cout << "in each word. Words must be at least four ";
   cout << "letters long and can be counted only once. ";
   cout << "You score points based on word length: a ";
   cout << "4-letter word is worth 1 point, 5-letters ";
   cout << "earn 2 points, and so on. After your puny ";
   cout << "brain is exhausted, I, the supercomputer, ";
   cout << "will find all the remaining words and double ";
   cout << "or triple your paltry score." << endl << endl;
   cout << "Hit return when you're ready...";
   getLine();
}

void playBoggle() {

    //  [TODO: Fill and extend code here]
    GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    gw.setLocation(50,50);
    initGBoggle(gw);

    drawBoard(4,4);
    StartGame();

    while (true) {


        if (!getYesOrNo("Would you like to play again? ")) break;
        reset();
        StartGame();
    }

    exitGraphics();
}
