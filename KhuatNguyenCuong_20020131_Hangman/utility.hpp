//
//  utility.hpp
//  KhuatNguyenCuong_20020131_Hangman
//
//  Created by Khuất Nguyên Cương on 4/12/21.
//

#ifndef utility_hpp
#define utility_hpp

#include <stdio.h>
#include <string>

struct ScoreSaved{
    std:: string Name;
    int Score;
    int TimePlayed;
    ScoreSaved(){};
    ScoreSaved(std:: string _Name, int _Score, int _TimePlayed)
    {
        Name = _Name;
        Score = _Score;
        TimePlayed = _TimePlayed;
    }
};

std :: string normalize(const std::string &s);
std :: string chooseWord(const std::string &fileName, int level);
bool contains(std::string word, char guess);
int getScore(int level, int plusMore, int Hint, std:: string word, int TimePlayed);
int getMaxScore(std:: string filename);
bool checkHighScore(int Score);
void SaveHighScore(ScoreSaved NewScore);
#endif /* utility_hpp */
