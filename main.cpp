#include <iostream>
#include "ReadData.h"
#include "ShuntingYard.h"
#include "text.h"

int main() {

    DefineVarCommand * com= new DefineVarCommand();
    com->addVar("x",30.5);

    ShuntingYard s("55-5+3", com);
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