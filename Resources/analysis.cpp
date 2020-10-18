//
// Created by Ridd on 2020/10/13/013.
//

#include "../Headers/analysis.h"

extern int state;
extern bool read;
extern tool cnt;

int analysisChar(std::string &token, char &inChar) {
    /*
     * Automata mode:
     * -1:error     0:start     1:inLetter      2:inDigit       3-7:number
     * 10-13:comment        14:jumpLine     20-23:operator      30-31:charOrString
     */
    switch (state) {
        case -1:
            std::cout << "Error at row " << cnt.rowCount << ": \"" << token << inChar << "\"" << std::endl;
            read = false;
            token.clear();
            state = 0;
            cnt.errCount++;
            break;

        case 0:
            read = false;
            token.clear();
            if (isLetter(inChar)) {
                token.push_back(inChar);
                state = 1;
            } else if (isDigit(inChar)) {
                token.push_back(inChar);
                state = 2;
            } else {
                switch (inChar) {
                    case '+':// x or x= or xx
                    case '-':
                    case '&':
                    case '|':
                        token.push_back(inChar);
                        state = 20;
                        break;

                    case '!':// x or x=
                    case '*':
                    case '%':
                    case '^':
                        token.push_back(inChar);
                        state = 21;
                        break;

                    case '/':// maybe // or /* or  /= or /
                        token.push_back(inChar);
                        state = 10;
                        break;

                    case '=':// x or xx
                        token.push_back(inChar);
                        state = 22;
                        break;

                    case '<':// x or xx or x= or xx=
                    case '>':
                        token.push_back(inChar);
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
                        token.push_back(inChar);
                        state = 0;
                        printTuple(token, "-");
                        cnt.othersCount++;
                        break;

                    case '\'':// char ahead
                        token.push_back(inChar);
                        state = 30;
                        break;

                    case '"':// a string ahead
                        token.push_back(inChar);
                        state = 31;
                        break;

                    case ' ':
                    case '\n':
                    case '\r':
                    case '\t':
                    case '\\':
                        break;

                    default:
                        state = -1;
                        read = true;
                        break;
                }
            }
            break;

        case 1:// identifier, includes _, letter, digit.
            if (isLetter(inChar) || isDigit(inChar)) {
                token.push_back(inChar);
            } else {// maybe space or others
                state = 0;
                read = true;
                if (isKeyword(token)) {
                    printTuple(token, "-");
                    cnt.keywordCount++;
                } else {
                    printTuple("identifier", token);
                    cnt.idCount++;
                }
            }
            break;

        case 2:// constant number
            if (isDigit(inChar)) {
                token.push_back(inChar);
            } else if (inChar == '.') {// number like 1.0
                token.push_back(inChar);
                state = 3;
            } else if (inChar == 'E' || inChar == 'e') {// number like 1ex or 1Ex
                token.push_back(inChar);
                state = 5;
            } else if(!isLetter(inChar)){// not digit, '.', E/e, end this
                state = 0;
                read = true;
                printTuple("constant", token);
                cnt.constCount++;
            } else{
                state = -1;
                read = true;
            }
            break;

        case 3:// constant number starts with "x."
            if (isDigit(inChar)) {
                token.push_back(inChar);
                state = 4;
            } else {// not expected char, error
                state = -1;
                read = true;
            }
            break;

        case 4:// constant number starts with "x.y"
            if (isDigit(inChar)) {
                token.push_back(inChar);
            } else if (inChar == 'E' || inChar == 'e') {
                token.push_back(inChar);
                state = 5;
            } else {
                state = 0;
                read = true;
                printTuple("constant", token);
                cnt.constCount++;
            }
            break;

        case 5:
            if (inChar == '+' || inChar == '-') {// number like 1e+6, 1e-6
                token.push_back(inChar);
                state = 6;
            } else if (isDigit(inChar)) {
                token.push_back(inChar);
                state = 7;
            } else {// syntax error
                state = -1;
                read = true;
            }
            break;

        case 6:
            if (isDigit(inChar)) {
                token.push_back(inChar);
                state = 7;
            } else {
                state = -1;
                read = true;
            }
            break;

        case 7:// number like 1e6
            if (isDigit(inChar)) {
                token.push_back(inChar);
            } else {
                state = 0;
                read = true;
                printTuple("constant", token);
                cnt.constCount++;
            }
            break;

        //states to check comments: 10-13
        case 10:// comment starts with '/'
            if (inChar == '/') {// comment like "//"
                state = 11;
            } else if (inChar == '*') {// comment like "/*"
                state = 12;
            } else if (inChar == '=') {// "/=" operator in C language
                token.push_back(inChar);
                state = 0;
                printTuple(token, "-");
            } else {// just a divide '/'
                state = 0;
                read = true;
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
                read = true;
            } else {// still in comment
                state = 12;
            }
            break;

        case 20:// x or x= or xx, x= + or - or < or >
            if (inChar == '=') {// being += or -=
                token.push_back(inChar);
                state = 0;
            } else if (inChar == token.back()) {// being ++ or --
                token.push_back(inChar);
                state = 0;
            } else {// being + or -
                state = 0;
                read = true;
            }
            printTuple("operator", token);
            cnt.opCount++;
            break;

        case 21:// * or *=, ! or !=
            if (inChar == '=') {// being *=
                token.push_back(inChar);
                state = 0;
            } else {// being *
                state = 0;
                read = true;
            }
            printTuple("operator", token);
            cnt.opCount++;
            break;

        case 22:// bool logic &, &&, |, || ; plus = or ==
            if (inChar == token.back()) {// being && or ||
                token.push_back(inChar);
                state = 0;
            } else {// being & or |
                state = 0;
                read = true;
            }
            printTuple("operator", token);
            cnt.opCount++;
            break;

        case 23:// x or x= or xx or xx=
            if (inChar == '=') {// being += or -=
                token.push_back(inChar);
                state = 0;
                printTuple("operator", token);
                cnt.opCount++;
            } else if (inChar == token.back()) {// maybe xx or xx=, goto case 21
                token.push_back(inChar);
                state = 21;
            } else {// being + or -
                state = 0;
                read = true;
                printTuple("operator", token);
                cnt.opCount++;
            }
            break;

        case 30:// skip char

            if (inChar == '\'') {
                if (token.length() == 2) {// char read
                    token.push_back(inChar);
                    state = 0;
                    printTuple("constant", token);
                    cnt.constCount++;
                } else {// char doesnt have 1 character
                    state = -1;
                    read = true;
                }
            } else if (token.size() >= 2) {
                state = -1;
                read = true;
            } else {
                token.push_back(inChar);
            }
            break;

        case 31:// skip string
            if (inChar == '"') {// maybe it's end of string, maybe it's \"
                if (token[token.length() - 1] == '\\') {
                    token.push_back(inChar);
                } else {
                    token.push_back(inChar);
                    state = 0;
                    printTuple("constant", token);
                    cnt.constCount++;
                }
            } else if (inChar == EOF) {// file finished without char end mark
                state = -1;
                read = true;
            } else {// just string
                token.push_back(inChar);
            }
            break;

        default:
            state = -1;
            read = true;
            break;
    }
    return 0;
}
