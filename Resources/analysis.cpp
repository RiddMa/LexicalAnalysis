//
// Created by Ridd on 2020/10/13/013.
//

#include "../Headers/analysis.h"
#include "../Headers/util.h"

extern int state;
extern int jumpLine;

int analysisChar(const char &inChar) {
    std::string token;
    /*
     * Automata mode:
     * -1:error     0:start     1:inLetter      2:inDigit       3-7:number
     * 10-13:comment        14:jumpLine     20-23:operator      30-31:charOrString
     */
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
                    case '+':// x or x= or xx
                    case '-':
                    case '&':
                    case '|':
                        token.append(to_string(inChar));
                        state = 20;
                        break;

                    case '!':// x or x=
                    case '*':
                    case '%':
                    case '^':
                        token.append(to_string(inChar));
                        state = 21;
                        break;

                    case '/':// maybe // or /* or  /= or /
                        token.append(to_string(inChar));
                        state = 10;
                        break;

                    case '=':// x or xx
                        token.append(to_string(inChar));
                        state = 22;
                        break;

                    case '<':// x or xx or x= or xx=
                    case '>':// why the fxxk there is <<= and >>=???
                        token.append(to_string(inChar));
                        state = 23;
                        break;

                    case '(':// only allows single char
                    case ')':// in lexical analysis you dont need to
                    case '[':// resolve the logical relationship
                    case ']':// between '('s and ')'s
                    case '{':
                    case '}':
                    case ';':
                    case '~':
                    case '?':
                    case ':':
                    case '.':
                    case ',':
                        token.append(to_string(inChar));
                        state = 0;
                        printTuple(token, "-");
                        break;

                    case '\'':// char ahead
                        token.append(to_string(inChar));
                        state = 30;
                        printTuple(token, "-");
                        break;

                    case '\"':// a string ahead
                        state = 31;

                    case ' ':
                    case '\n':
                    case '\r':
                    case '\t':
                        break;

                    default:
                        state = -1;
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

            //states to check comments: 10-13
        case 10:// comment starts with '/'
            if (inChar == '/') {// comment like "//"
                state = 11;
            } else if (inChar == '*') {// comment like "/*"
                state = 12;
            } else if (inChar == '=') {// "/=" operator in C language
                token.append(to_string(inChar));
                state = 0;
                printTuple(token, "-");
            } else {// just a divide '/'
                state = 0;
                printTuple("operator", "/");
            }
            break;

        case 11:// "//" comment, skip
            state = 14;//set to skip line mode
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

        case 20:// x or x= or xx, x= + or - or < or >
            if (inChar == '=') {// being += or -=
                token.append(to_string(inChar));
                state = 0;
            } else if (inChar == token.back()) {// being ++ or --
                token.append(to_string(inChar));
                state = 0;
            } else {// being + or -
                state = 0;
            }
            printTuple("operator", token);
            break;

        case 21:// * or *=, ! or !=
            if (inChar == '=') {// being *=
                token.append(to_string(inChar));
                state = 0;
            } else {// being *
                state = 0;
            }
            printTuple("operator", token);
            break;

        case 22:// bool logic &, &&, |, || ; plus = or ==
            if (inChar == token.back()) {// being && or ||
                token.append(to_string(inChar));
                state = 0;
            } else {// being & or |
                state = 0;
            }
            printTuple("operator", token);
            break;

        case 23:// x or x= or xx or xx=
            if (inChar == '=') {// being += or -=
                token.append(to_string(inChar));
                state = 0;
                printTuple("operator", token);
            } else if (inChar == token.back()) {// maybe xx or xx=, goto case 21
                token.append(to_string(inChar));
                state = 21;
            } else {// being + or -
                state = 0;
                printTuple("operator", token);
            }
            break;

        case 30:// skip char
            if (inChar == '\'') {
                if (token.length() == 2) {// char read
                    token.append(to_string(inChar));
                    state = 0;
                    printTuple("constant", token);
                } else {// char doesnt have 1 character
                    state = -1;
                }
            } else if (inChar == EOF) {// file finished without char end mark
                state = -1;
            } else {
                token.append(to_string(inChar));
            }
            break;

        case 31:// skip string
            if (inChar == '\"') {// maybe it's end of string, maybe it's \"
                if (token[token.length() - 2] == '\\') {
                    token.append(to_string(inChar));
                } else {
                    token.append(to_string(inChar));
                    state = 0;
                    printTuple("constant", token);
                }
            } else if (inChar == EOF) {// file finished without char end mark
                state = -1;
            } else {// just string
                token.append(to_string(inChar));
            }
            break;

        default:
            state = -1;
            break;
    }


    return 0;
}

int analysisLine(const std::string &inLine) {

    std::string token;

    for (char i : inLine) {
        if (state == 14) {// remain of this line is comment
            return 0;
        } else {
            token.append(std::to_string(i));
            analysisChar(i);
        }
    }

    return 0;
}
