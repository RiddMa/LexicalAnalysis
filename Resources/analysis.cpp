//
// Created by Ridd on 2020/10/13/013.
//

#include "../Headers/analysis.h"

int analysisChar(char inChar) {
    switch (inChar) {

    }
}

int analysisLine(string inLine) {
    // remove all spaces in front
    inLine.erase(0,inLine.find_first_not_of(" "));

    int len = inLine.length();

    for (int i = 0; i < len; i++) {
        analysisChar(inLine[i]);
    }
}