//
// Created by 马嘉骥 on 2020/10/13.
//

#include "../Headers/util.h"

//extern std::vector<std::string> reserveWord;
bool isReserveWord(const string &inString, const std::vector<std::string> &reserveWord) {
    for (const auto &i : reserveWord) {
        if (inString == i)
            return true;
    }
    return false;
}

int writeLine(std::fstream &infile, std::vector<std::string> &buf) {
    std::string tmpStr;
    getline(infile, tmpStr);
    buf.push_back(tmpStr);
}

bool printTuple() {

}