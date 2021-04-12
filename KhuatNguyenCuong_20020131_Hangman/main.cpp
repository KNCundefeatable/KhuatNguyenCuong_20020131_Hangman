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

using namespace std;

char readAGuess()
{
    char guess;
    cout << "Please enter your next guess: ";
    cin >> guess;
    return guess;
}

void update(string& guessedWord, const string& word, char guess)
{
    unsigned long int n = guessedWord.length();
    for (int i = 0; i < n; i++) {
        if (word[i] == guess)
            guessedWord[i] = guess;
    }
}

int main(int argc, char* argv[])
{
    srand(static_cast<unsigned int>(time(nullptr))); //random seeds
    string fileName = argc > 1 ? argv[1] : "/Users/knc/Documents/KhuatNguyenCuong_20020131_Hangman/KhuatNguyenCuong_20020131_Hangman/ogden_picturable_200.txt";

    while (true) {
        string word = chooseWord(fileName);
        if (word.empty()) {
            cout << "No word available in " << fileName << endl;
            return 0;
        }
        string guessedWord = string(word.length()-1, '-');
        int badGuessCount = 0;
        const int MAX_BAD_GUESS = 7;
        string badGuess;

        do {
            renderGame(guessedWord, badGuessCount, badGuess);
            char guess = readAGuess();

            if (contains(word, guess)) {
                update(guessedWord, word, guess);
            } else {
                badGuessCount++;
                badGuess += guess;
            }
        } while (badGuessCount < MAX_BAD_GUESS && guessedWord != word);

        printGameOverInfo(guessedWord, word, badGuessCount);
        cout << "Do you want more (Y/N) ?";
        string answer;
        cin.ignore(1);
        getline(cin, answer);
        if (answer != "Y" && answer != "y")
            break;
    }

    return 0;
}

