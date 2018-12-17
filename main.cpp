#include <iostream>
#include "ReadData.h"
#include "ShuntingYard.h"
int main() {

    ShuntingYard s= ShuntingYard("25+6");

    ReadData x;
    x.lexer("data");


    for (auto &s : x.getVector()) {
        for (auto m:s) {
            cout << m << " ";
        }
        cout << endl;
    }
    //do the script
    //x.parser();

    return 0;
}