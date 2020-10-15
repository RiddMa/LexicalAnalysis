//
// Created by 马嘉骥 on 2020/10/13.
//

#include "../Headers/util.h"

bool isLetter(const char inChar) {
    return (isalpha(inChar) || inChar == '_');
}

bool isDigit(const char inChar) {
    return (isdigit(inChar) == true);
}


bool isReserveWord(const string &inString) {

    for (const auto &i : reserveWord) {
        if (inString == i)
            return true;
    }
    return false;
}


int file2Buf(std::ifstream &infile, std::vector<std::string> &buf) {
    std::string tmpStr;
    while (std::getline(infile, tmpStr)) {
        tmpStr.erase(0, tmpStr.find_first_not_of(' '));
        buf.push_back(tmpStr);
    }
    return 0;
}


void printTuple(std::string type, std::string attr) {
    std::cout << "<" + type + "," + attr + ">" << std::endl;
}