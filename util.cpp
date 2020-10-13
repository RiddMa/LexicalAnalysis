//
// Created by 马嘉骥 on 2020/10/13.
//

#include "util.h"

//extern std::vector<std::string> reserveWord;
bool isReserveWord(const string &inString, const std::vector<std::string> &reserveWord) {
    for (const auto &i : reserveWord) {
        if (inString == i)
            return true;
    }
    return false;
}

bool printTuple() {

}