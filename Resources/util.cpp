//
// Created by 马嘉骥 on 2020/10/13.
//

#include "../Headers/util.h"

std::string keyword[] = {
        "auto", "break", "case", "char", "const", "continue",
        "default", "do", "double", "else", "enum", "extern",
        "float", "for", "goto", "if", "int", "long",
        "register", "return", "short", "signed", "sizeof", "static",
        "struct", "switch", "typedef", "union", "unsigned", "void",
        "volatile", "while"
};

bool isLetter(const char inChar) {
    return (isalpha(inChar) || inChar == '_');
}

bool isDigit(const char inChar) {
    return (isdigit(inChar) != 0);
}

bool isKeyword(const std::string &inString) {

    for (const auto &i : keyword) {
        if (inString == i)
            return true;
    }
    return false;
}

int file2Buf(std::ifstream &infile, std::vector<std::string> &buf) {
    std::string tmpStr;
    while (std::getline(infile, tmpStr)) {
        tmpStr.erase(0, tmpStr.find_first_not_of(' '));
        buf.push_back(tmpStr + '\n');
    }
    return 0;
}

void printTuple(const std::string &type, const std::string &attr) {
    std::cout << "<" + type + "," + attr + ">" << std::endl;
}