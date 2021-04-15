//
//  main.cpp
//  KhuatNguyenCuong_20020131_Hangman
//
//  Created by Khuất Nguyên Cương on 4/12/21.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>

#include "draw.hpp"
#include "utility.hpp"
#include "core.hpp"

using namespace std;


int main(int argc, char* argv[])
{
    srand(static_cast<unsigned int>(time(nullptr))); //random seeds
    
    core* hangman = new core();
    
    while (hangman->Playing) {
        hangman->initWord();
        

        do {
            hangman->renderGame();
            hangman->readAGuess();
            hangman->updateBadGuess();
        } while (hangman->checkWinYet());

        hangman->printGameOverInfo();
        
        hangman->gameContinue();
    }

    return 0;
}

