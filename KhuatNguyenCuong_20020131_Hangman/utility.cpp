//
//  utility.cpp
//  KhuatNguyenCuong_20020131_Hangman
//
//  Created by Khuất Nguyên Cương on 4/12/21.
//


#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "utility.hpp"

using namespace std;

string normalize(const string& s)
{
    string news = s;
    transform(s.begin(), s.end(), news.begin(), ::tolower);
    return news;
}

string chooseWord(const string &fileName)
{
    vector<string> vocabulary;
    ifstream file(fileName);
    if (!file.is_open())
        return "";

    while (!file.eof()) {
        string line;
        file >> line;
        if (file && !line.empty())
            vocabulary.push_back(normalize(line));
    }
    srand(static_cast<unsigned int>(time(nullptr))); //random seeds
    unsigned long int n = vocabulary.size();
    cout << "vocabulary size = " << n << endl;
    string word  = vocabulary[rand() % n];
    cout << word.length() << endl;
    return n > 0 ? word : "";
}

bool contains(string word, char guess)
{
    return (word.find(guess) != string::npos);
}

