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
    ReadData x;
    /**
     * check if there is one word input, so its fileName
     */
    if (argc == 2) {
        x.lexer(argv[1]);
    } else {
        string input;
        vector<vector<string>> v;
        cout << "Enter mission for me, mister checker" << endl;
        getline(cin, input);
        while ((input != "exit") && (input != "quit")) {
            v.push_back(x.arrangeVector(input));
            getline(cin, input);
        }
        x.setVec(v);
    }
    /**
     * parse the file or the input
     */
    x.parser();
    cout << endl << "ByeBye! Nice to meet you" << endl;
}