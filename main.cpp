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

    if (argc == 2) {
        ReadData x;
        x.lexer(argv[1]);
        x.parser();
    } else {
        string input;
        vector<vector<string>> v;
        ReadData x;
        cout << "Enter mission for me, mister checker" << endl;
        getline(cin, input);

        while (input != "exit") {
            v.push_back(x.arrangeVector(input));
            getline(cin, input);
        }
        x.setVec(v);
        x.parser();
        cout << "ByeBye! Nice to meet you" << endl;
    }


    int y;
    cin >> y;
    return 0;
}