#include <iostream>
#include "ReadData.h"
#include "ShuntingYard.h"
#include "text.h"

int main() {
    ShuntingYard s("55-5+3", nullptr);
    s.calculate();
    //  cout<<s.calculate()<<endl;
    //ReadData x;
    /*
    x.lexer("data");


    for (auto &s : x.getVector()) {
        for (auto m:s) {
            cout << m << " ";
        }
        cout << endl;
    }
    //do the script
    //x.parser();
*/
    return 0;
}