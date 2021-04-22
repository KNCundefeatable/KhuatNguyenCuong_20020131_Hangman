//
//  core.hpp
//  KhuatNguyenCuong_20020131_Hangman
//
//  Created by Khuất Nguyên Cương on 4/12/21.
//

#ifndef core_hpp
#define core_hpp

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>

#include "utility.hpp"

using namespace std;


class core
{

private:
    string word;
    string YNFullWord;
    string guessFullWord;
    string guessedWord;
    char guess;
    int badGuessCount;
    const int MAX_BAD_GUESS = 7;
    int level;
    string badGuess;
    //bool Quit;
    
public:
    bool Playing;
    core();
    void initWord();                            //initialize Word
    void chooseLevel();                         //choose optional level
    void readAGuess();                          //read a input_char
    void updateGuessedWord();                   //update Guessed Word
    void updateBadGuess();                      //update Bad Guess Count && list of Bad Guess
    void gameContinue ();                       //Y or N
    void clearScreen();                         //cls
    void renderGame();
    bool checkWinorLoseYet();                         //Win or not
    void printGameOverInfo();                   //Print Game Over Info
    
};

string getHangPicture(int a);


#endif /* core_hpp */
