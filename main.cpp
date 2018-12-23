/*****************************
 * Project of:
 * Ori Kopel 205533151
 * Shlomo Rabinovich 308432517
 * December 18
 ******************************/

#include <iostream>
#include "ReadData.h"
#include "ShuntingYard.h"
#include <list>

int main(int argc, char **argv) {

    if (argc < 1) {
        throw "Give me a file please!!!";
    }
    ReadData x;
    x.lexer(argv[1]);
    x.parser();

    int y;
    cin >> y;
    return 0;
}