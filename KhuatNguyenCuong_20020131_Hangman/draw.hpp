//
//  draw.hpp
//  KhuatNguyenCuong_20020131_Hangman
//
//  Created by Khuất Nguyên Cương on 4/12/21.
//

#ifndef draw_hpp
#define draw_hpp

#include <stdio.h>
#include <string>

std::string getHangPicture(int badGuessCount);
void clearScreen();
void renderGame(std::string guessedWord, int badGuessCount, std::string badGuess);
void printGameOverInfo(std::string guessedWord, std::string word, int badGuessCount);
#endif /* draw_hpp */
