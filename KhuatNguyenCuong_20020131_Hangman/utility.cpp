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

string chooseWord(const string &fileName, int level)
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
    
    if(level == 1)
    {
        while(word.size()>4)
        {
            word  = vocabulary[rand() % n];
        }
    }
    else if(level == 2)
    {
        while(word.size()<4 || word.size() >6)
        {
            word  = vocabulary[rand() % n];
        }
    }
    else if(level == 3)
    {
        while(word.size() <=6)
        {
            word  = vocabulary[rand() % n];
        }
    }
    return n > 0 ? word : "";
}

bool contains(string word, char guess)
{
    return (word.find(guess) != string::npos);
}

int getScore(int level, int plusMore, int Hint)
{
    int Score;
    if(level < 4)
    {
        Score = level*100 + 20*(plusMore);
    }
    else{
        Score = 500;
    }
    if(Hint==0) return Score;
    return Score - 40;
}
int getMaxScore(std:: string filename)
{
    ifstream file;
    file.open(filename);
    if (!file.is_open())
        return 0;
    vector<int>ListofScore(5);
    string line;
    getline(file, line);
    while (!file.eof()) {
        string name;
        file>> name;
        int Score;
        file >> Score;
        int time;
        file >> time;
        getline(file,line);
        ListofScore.push_back(Score);
        sort(ListofScore.begin(), ListofScore.end());
    }
    return ListofScore[ListofScore.size()-1];
}

bool checkHighScore(int Score)
{
    int MaxScore = getMaxScore("/Users/knc/Documents/KhuatNguyenCuong_20020131_Hangman/KhuatNguyenCuong_20020131_Hangman/Score/SaveHighScore.txt");
    if(Score > MaxScore) return true;
    return false;
}

void SaveHighScore(ScoreSaved NewScore)
{
        ofstream file;
        file.open("/Users/knc/Documents/KhuatNguyenCuong_20020131_Hangman/KhuatNguyenCuong_20020131_Hangman/Score/SaveHighScore.txt",std :: ios :: app);
        file << setfill(' ') << setw(11) << NewScore.Name;
        file << setfill(' ') << setw(10) << NewScore.Score;
        file << setfill(' ') << setw(16) << NewScore.TimePlayed;
        file << endl;
        file.close();
}

