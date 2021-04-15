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

#include "utility.hpp"

using namespace std;


class core
{

private:
    string word;
    string guessedWord;
    char guess;
    int badGuessCount;
    const int MAX_BAD_GUESS = 7;
    string badGuess;
    //bool Quit;
    
public:
    bool Playing;
    core();
    void initWord();
    void readAGuess();
    void updateGuessedWord();
    void updateBadGuess();
    void gameContinue ();
    
    void clearScreen();
    void renderGame();
    bool checkWinYet();
    void printGameOverInfo();
    
};

string getHangPicture(int a);


#endif /* core_hpp */
