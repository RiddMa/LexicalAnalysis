//
// Created by Ridd on 2020/10/13/013.
//

#include "../Headers/analysis.h"
#include "../Headers/util.h"

int analysisChar(char inChar) {
    if(isLetter(inChar)){

    }
    else if(isDigit(inChar)){

    }

    /*switch (inChar) {
        case -1: {
            std::cout << "Error encountered." << std::endl;

        }
    }*/
    return 0;
}

int analysisLine(std::string inLine) {

    std::string token;

    for (int i = 0; i < inLine.length(); i++) {
        token.append(std::to_string(inLine[i]));
        analysisChar(inLine[i]);
    }
    return 0;
}
