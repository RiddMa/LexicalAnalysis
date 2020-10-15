//
// Created by 马嘉骥 on 2020/10/13.
//

#ifndef LEX_UTIL_H
#define LEX_UTIL_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;


class tool {

};

bool isLetter(const char inChar);

bool isDigit(const char inChar);

int file2Buf(std::ifstream &infile, std::vector<std::string> &buf);

bool isReserveWord(const string &inString);

void printTuple(std::string type, std::string attr);

#endif //LEX_UTIL_H
