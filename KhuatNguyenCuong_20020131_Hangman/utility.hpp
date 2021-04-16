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

std :: string normalize(const std::string &s);
std :: string chooseWord(const std::string &fileName);
bool contains(std::string word, char guess);

#endif /* utility_hpp */
