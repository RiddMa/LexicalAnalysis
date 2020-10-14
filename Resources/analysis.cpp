//
// Created by Ridd on 2020/10/13/013.
//

#include "../Headers/analysis.h"

int analysisChar(char inChar) {
    switch (inChar) {

    }
    return 0;
}

int analysisLine(string inLine) {

    int len = inLine.length();

    for (int i = 0; i < len; i++) {
        analysisChar(inLine[i]);
    }
    return 0;
}
