//
//  main.cpp
//  KhuatNguyenCuong_20020131_Hangman
//
//  Created by Khuất Nguyên Cương on 4/12/21.
//

#include "utility.hpp"
#include "core.hpp"

using namespace std;


int main(int argc, char* argv[])
{
    srand(static_cast<unsigned int>(time(nullptr))); //random seeds
    
    core* hangman = new core();

    while (hangman->Playing) {
        hangman ->chooseLevel();
        hangman->initWord();
        do {
            hangman->renderGame();
            hangman->readAGuess();
            hangman->updateBadGuess();
        }while (hangman->checkWinorLoseYet());
        
        hangman->printGameOverInfo();
        
        hangman->gameContinue();
    }
    
    return 0;
}

