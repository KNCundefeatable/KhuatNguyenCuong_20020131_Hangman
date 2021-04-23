//
//  core.cpp
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
#include <curses.h>
#include <unistd.h>
#include <term.h>

#include "core.hpp"

using namespace std;

string picture[] = {"",
    "   ------------\n"
    "   |           \n"
    "   |           \n"
    "   |           \n"
    "   |           \n"
    "   |           \n"
    "   |           \n"
    "   |           \n"
    "   |           \n"
    "-------        ",
    "   ------------\n"
    "   |          |\n"
    "   |          O\n"
    "   |           \n"
    "   |           \n"
    "   |           \n"
    "   |           \n"
    "   |           \n"
    "   |           \n"
    "-------        ",
    "   ------------\n"
    "   |          |\n"
    "   |          O\n"
    "   |          |\n"
    "   |           \n"
    "   |           \n"
    "   |           \n"
    "   |           \n"
    "   |           \n"
    "-------        ",
    "   ------------\n"
    "   |          |\n"
    "   |          O\n"
    "   |         /|\n"
    "   |           \n"
    "   |           \n"
    "   |           \n"
    "   |           \n"
    "   |           \n"
    "-------        ",
    "   ------------\n"
    "   |          |\n"
    "   |          O\n"
    "   |         /|\\\n"
    "   |           \n"
    "   |           \n"
    "   |           \n"
    "   |           \n"
    "   |           \n"
    "-------        ",
    "   ------------\n"
    "   |          |\n"
    "   |          O\n"
    "   |         /|\\\n"
    "   |         / \n"
    "   |           \n"
    "   |           \n"
    "   |           \n"
    "   |           \n"
    "-------        ",
    "   ------------\n"
    "   |          |\n"
    "   |          O\n"
    "   |         /|\\\n"
    "   |         / \\\n"
    "   |           \n"
    "   |           \n"
    "   |           \n"
    "   |           \n"
    "-------        ",
};


core::core()
{
    Playing = true;
    badGuessCount = 0;
}

void core:: chooseLevel()
{
    clearScreen();
    cout << "Please choose the level you want: " << endl;
    cout << "1. Easy" << endl << "2. Medium" << endl << "3. Hard" << endl << "4. One shot" << endl;
    cin >> level;
}

void core:: initWord()
{
    word = chooseWord("/Users/knc/Downloads/ogden_picturable_200.txt", level);
    guessedWord = string(word.length(),'-');
}

void core:: HintFunction()
{
    int position;
    if(callHint==0)
    {
        cout << "Press 0 if you wanna a hint" << endl << endl;
    }
    if(guess == '0')
    {
        callHint = 1;
        clearScreen();
        cout << "The word is: " << guessedWord << endl;
        cout << "Please choose the position of the character you want: ";
        cin >> position;
        clearScreen();
        guessedWord[position-1] = word[position-1];
        updateGuessedWord();
    }
}

void core:: readAGuess()
{
    cout << "Please enter your next guess: ";
    cin >> guess;
}

void core:: updateGuessedWord()
{
    unsigned long n = guessedWord.length();
    for (int i = 0; i < n; i++) {
        if (word[i] == guess)
            guessedWord[i] = guess;
    }
}

void core:: updateBadGuess()
{
    if (contains(word, guess) || guess == '0') {
        updateGuessedWord();
    } else {
        badGuessCount++;
        badGuess += guess;
    }
}

void core:: gameContinue ()
{
    cout << "Do you want more (Y/N) ?";
    string answer;
    cin.ignore(1);
    getline(cin, answer);
    if (answer == "N" || answer == "n")
    {
        //Quit = true;
        Playing = false;
    }
    else if(answer == "Y" || answer == "y")
    {
        //Quit = false;
        Playing = true;
        badGuessCount = 0;
        badGuess = "";
    }
}

string getHangPicture(int a)
{
    return picture[a];
}

void core:: clearScreen()
{
    system("clear");
}

void core:: renderGame()
{
    clearScreen();
    HintFunction();
    //cout << "The length of word is: " << word.length() << endl;
    cout << "Current guess = " << guessedWord << endl;
    cout << "You have made bad " << badGuessCount << " guess(es)"
    << (badGuess.empty() ? "" : ": ") << badGuess << endl
    << getHangPicture(badGuessCount) << endl;
}

const vector<string> HANGED = {
    "   ------------\n"
    "   |         /\n"
    "   |        O\n"
    "   |       /|\\\n"
    "   |       / \\\n"
    "   |         \n"
    "   |         \n"
    "   |         \n"
    "   |         \n"
    "-------        ",
    "   ------------\n"
    "   |          |\n"
    "   |          O\n"
    "   |         /|\\\n"
    "   |         / \\\n"
    "   |           \n"
    "   |           \n"
    "   |           \n"
    "   |           \n"
    "-------        ",
    "   ------------\n"
    "   |           \\\n"
    "   |            O\n"
    "   |           /|\\\n"
    "   |           / \\\n"
    "   |             \n"
    "   |             \n"
    "   |             \n"
    "   |             \n"
    "-------        ",
    "   ------------\n"
    "   |          |\n"
    "   |          O\n"
    "   |         /|\\\n"
    "   |         / \\\n"
    "   |           \n"
    "   |           \n"
    "   |           \n"
    "   |           \n"
    "-------        "
};

bool core:: checkWinorLoseYet()
{
    if(level == 4)
    {
        badGuessCount = 7;
    }
    if(badGuessCount < MAX_BAD_GUESS && guessedWord != word) return true;
    return false;
}

void core:: printGameOverInfo()
{
    renderGame();
    if (guessedWord != word) {
        int n = 0;
        int count_to_reset = 0;
        while (count_to_reset+=10) {
            clearScreen();
            cout << "Game Over!!! You are hanged" << endl
            << "The correct word is " << word << endl;
            cout << HANGED[n];
            n = (n+1) % HANGED.size();
            std::this_thread::sleep_for (std::chrono::milliseconds(500));
            if(count_to_reset>50)
                break;
        }
    }
    else {
        cout << "Congrats!!! You are free" << endl;
    }
}


