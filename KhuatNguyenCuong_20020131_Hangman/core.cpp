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
#include "utility.hpp"

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

void core:: chooseCategory()
{
    clearScreen();
    getTimeStart();
    cout << "Please choose the category of the word: " << endl;
    cout << "1. Animals" << endl << "2. City" << endl << "3. Clothes" << endl << "4. Environment" << endl << "5. Family" << endl << "6. Fruits" << endl << "7. Jobs" << endl;
    cin >> category;
}

string core:: initCategory()
{
    switch(category)
    {
        case 1:
            categoryName = "Animals.txt";
            break;
        case 2:
            categoryName = "City.txt";
            break;
        case 3:
            categoryName = "Clothes.txt";
            break;
        case 4:
            categoryName = "Environment.txt";
            break;
        case 5:
            categoryName = "Family.txt";
            break;
        case 6:
            categoryName = "Fruits.txt";
            break;
        case 7:
            categoryName = "Jobs.txt";
            break;
    }
    return categoryName;
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
    string LinkCategory = initCategory();
    word = chooseWord("/Users/knc/Downloads/"+LinkCategory, level);
    guessedWord = string(word.length(),'-');
}

void core:: HintFunction()
{
    if(level<4){
        int position;
        if(callHint==0)
        {
            cout << "Press 0 if you wanna a hint" << endl << endl;
        }
        if(guess == '0' && flagHint == 0)
        {
            callHint = 1;
            flagHint = 1;
            clearScreen();
            cout << "The word is: " << guessedWord << endl;
            cout << "Please choose the position of the character you want: ";
            cin >> position;
            clearScreen();
            guessedWord[position-1] = word[position-1];
            updateGuessedWord();
        }
    }
}

void core:: readAGuess()
{
    if(guessedWord != word){
        cout << "Please enter your next guess: ";
        if(level<4)
        {
            cin >> guess;
        }
        else{
            cin >> guessFullWord;
        }
    }
}
void core:: updateGuessedWord()
{
    unsigned long n = guessedWord.length();
    if(level < 4){
        for (int i = 0; i < n; i++) {
            if (word[i] == guess)
                guessedWord[i] = guess;
        }
    }
    else{
        if(guessFullWord == word)
        {
            guessedWord = guessFullWord;
        }
    }
}

void core:: updateBadGuess()
{
    if(level<4){
        if (contains(word, guess) || (guess == '0' && flagHint == 0) || (guessedWord == word)) {
            updateGuessedWord();
        }
        else {
            badGuessCount++;
            badGuess += guess;
        }
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
        callHint = 0;
        flagHint = 0;
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

void core:: getTimeStart() {
//    time_t     now = time(0);
//    struct tm  tstruct;
//    char       buf[80];
//    tstruct = *localtime(&now);
//    strftime(buf, sizeof(buf), "%Y-%m-%d || %X", &tstruct);
//    TimeStart = buf;
    time_t now = time(0);
    time(&startTime);
    TimeStart = ctime(&now);
    cout << "Time Start: " << TimeStart << endl << endl;
}

void core:: getTimeFinish() {
//    time_t     now = time(0);
//    struct tm  tstruct;
//    char       buf[80];
//    tstruct = *localtime(&now);
//    strftime(buf, sizeof(buf), "%Y-%m-%d || %X", &tstruct);
//    TimeFinish = buf;
    time_t now = time(0);
    TimeFinish = ctime(&now);
    cout << "Time Finish: " << TimeFinish << endl << endl;
}

int core:: getTimeDone()
{
    time_t now = time(0);
    time(&now);
    TimePlayed = difftime(now, startTime);
    return TimePlayed;
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
        Score = getScore(level, MAX_BAD_GUESS-badGuessCount, callHint);
        cout << "Congrats!!! You are free" << endl;
        cout << "Your Score is: " << Score << endl;
        getTimeFinish();
        TimePlayed = getTimeDone();
        cout << "Time played: " << TimePlayed << " (seconds) " << endl;
    }
}

bool core:: checkHighScore()
{
    int MaxScore = getMaxScore("/Users/knc/Documents/KhuatNguyenCuong_20020131_Hangman/KhuatNguyenCuong_20020131_Hangman/Score/New High Score");
    if(Score > MaxScore) return true;
    return false;
}

//void core:: SaveHighScore()
//{
//    if(checkHighScore())
//    {
//        ofstream file;
//        file.open("/Users/knc/Documents/KhuatNguyenCuong_20020131_Hangman/KhuatNguyenCuong_20020131_Hangman/Score/New High Score");
//        file << Score;
//        file.close();
//    }
//}
//
//void core:: SaveName()
//{
//    if(checkHighScore())
//    {
//        ofstream file;
//        file.open("/Users/knc/Documents/KhuatNguyenCuong_20020131_Hangman/KhuatNguyenCuong_20020131_Hangman/Score/New High Score");
//        string Name;
//        getline(cin, Name);
//        file << Name;
//        file.close();
//    }
//}
