#include <iostream>
#include "ReadData.h"

int main() {
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