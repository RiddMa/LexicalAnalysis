//
// Created by Ridd on 2020/10/13/013.
//

#include "../Headers/analysis.h"
#include "../Headers/util.h"

extern int state;

int analysisChar(char inChar) {
    std::string token;
    int jumpLine(0);

    switch (state) {
        case -1:
            std::cout << "Error encountered." << std::endl;
            exit(-1);

        case 0:
            if (isLetter(inChar)) {
                token.append(to_string(inChar));
                state = 1;
            } else if (isDigit(inChar)) {
                token.append(to_string(inChar));
                state = 2;
            } else {
                switch (inChar) {
                    case '/':
                        token.append(to_string(inChar));
                        state = 10;
                        break;

                }
            }
            break;

        case 1:// identifier, includes _, letter, digit.
            if (isLetter(inChar) || isDigit(inChar)) {
                token.append(to_string(inChar));
            } else {// maybe space or others
                state = 0;
                if (isReserveWord(token)) {
                    printTuple(token, "-");
                } else {
                    printTuple("identifier", token);
                }
            }
            break;

        case 2:// constant number
            if (isDigit(inChar)) {
                token.append(to_string(inChar));
            } else if (inChar == '.') {// number like 1.0
                token.append(to_string(inChar));
                state = 3;
            } else if (inChar == 'E' || inChar == 'e') {// number like 1ex or 1Ex
                token.append(to_string(inChar));
                state = 5;
            } else {// not digit, '.', E/e, end this
                state = 0;
                printTuple("constant", token);
            }
            break;

        case 3:// constant number starts with "x."
            if (isDigit(inChar)) {
                token.append(to_string(inChar));
                state = 4;
            } else {// not expected char, error
                state = -1;
            }
            break;

        case 4:// constant number starts with "x.y"
            if (isDigit(inChar)) {
                token.append(to_string(inChar));
            } else if (inChar == 'E' || inChar == 'e') {
                token.append(to_string(inChar));
                state = 5;
            } else {
                state = 0;
                printTuple("constant", token);
            }
            break;

        case 5:
            if (inChar == '+' || inChar == '-') {// number like 1e+6, 1e-6
                token.append(to_string(inChar));
                state = 6;
            } else if (isDigit(inChar)) {
                token.append(to_string(inChar));
                state = 7;
            } else {// syntax error
                state = -1;
            }
            break;

        case 6:
            if (isDigit(inChar)) {
                token.append(to_string(inChar));
                state = 7;
            } else {
                state = -1;
            }
            break;

        case 7:// number like 1e6
            if (isDigit(inChar)) {
                token.append(to_string(inChar));
            } else {
                state = 0;
                printTuple("constant", token);
            }
            break;

        case 10:// comment starts with '/'
            if (inChar == '/') {// comment like "//"
                state = 11;
            } else if (inChar == '*') {// comment like "/*"
                state = 12;
            } else if (inChar == '=') {// "/=" operator in C language
                token.append(to_string(inChar));
                state = 0;
                printTuple("/=", "-");
            } else {// just a divide '/'
                state = 0;
                printTuple("operator", "/");
            }
            break;

        case 11:// "//" comment, skip
            jumpLine = 1;
            break;

        case 12:// inside "/*" comment
            if (inChar == '*') {
                state = 13;
            }//else still in comment
            break;

        case 13:// will comment "/*" end?
            if (inChar == '/') {// comment "/*...*/" detected
                state = 0;
            } else if (inChar == EOF) {// file finished without comment end mark
                state = -1;
            } else {// still in comment
                state = 12;
            }
            break;

        case 14:

    }


    /*switch (inChar) {
        case -1: {


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
