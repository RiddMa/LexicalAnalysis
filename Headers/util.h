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

public:
    int rowCount;
    int charCount;
    int idCount;
    int keywordCount;
    int opCount;
    int constCount;
    int othersCount;


public:
    void clear() {
        rowCount = 0;
        charCount = 0;
        idCount = 0;
        keywordCount = 0;
        opCount = 0;
        constCount = 0;
        othersCount = 0;
    }

    int getTotalCount() {
        return idCount + keywordCount + opCount + constCount + othersCount;
    }
};

bool isLetter(const char inChar);

bool isDigit(const char inChar);

int file2Buf(std::ifstream &infile, std::vector<std::string> &buf);

bool isKeyword(const std::string &inString);

void printTuple(const std::string &type, const std::string &attr);

#endif //LEX_UTIL_H
