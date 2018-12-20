#include <iostream>
#include "ReadData.h"
#include "ShuntingYard.h"
#include "text.h"
#include <list>

int main() {
/*
    DefineVarCommand * com= new DefineVarCommand();
    com->addVar("x",30.5);

    ShuntingYard s("x-000000000000.222", com);
    s.calculate();*/

    cout << ShuntingYard("10-5-1", nullptr).calculate() << "=4" << endl;
    cout << ShuntingYard("20+2*6", nullptr).calculate() << "=32" << endl;
    cout << ShuntingYard("10*2+6", nullptr).calculate() << "=26" << endl;
    cout << ShuntingYard("2+4+6", nullptr).calculate() << "=12" << endl;
    cout << ShuntingYard("1+1+1+1+1+1", nullptr).calculate() << "=6" << endl;
    cout << ShuntingYard("1*2*3*4*5", nullptr).calculate() << "=120" << endl;
    cout << ShuntingYard("1+2*3+4/5+5*5", nullptr).calculate() << "=32.8" << endl;
    cout << ShuntingYard("25*2/2/2/2*2.1531*2*2.2654+2+2+2*2-2+2/8+4+5.2*4.5", nullptr).calculate() << "=94.6204" << endl;
    cout << ShuntingYard("25*2/2/2/2", nullptr).calculate() << "=6.25" << endl;

//    ShuntingYard e("5 - + - 3", nullptr);
//    cout << e.calculate() << endl;
//    ShuntingYard e0("5 + - + 3", nullptr);
//    cout << e0.calculate() << endl;
//    ShuntingYard e1("5 - - 3", nullptr);
//    cout << e1.calculate() << endl;
//    ShuntingYard e2("3 - + 10", nullptr);
//    cout << e2.calculate() << endl;
//    ShuntingYard e22("3 + - 10", nullptr);
//    cout << e22.calculate() << endl;
//    ShuntingYard e3("3 * - 10", nullptr);
//    cout << e3.calculate() << endl;
//    ShuntingYard e31("3 * + 10", nullptr);
//    cout << e31.calculate() << endl;
//    ShuntingYard e32("81 / - 9", nullptr);
//    cout << e32.calculate() << endl;
//    ShuntingYard e33("81 / + 9", nullptr);
//    cout << e33.calculate() << endl;
//     ShuntingYard f  (" - ( - 2 + 4)",nullptr);
    //  list1.push_back(f);
//     ShuntingYard g  (" - ( - 6 / - 2)",nullptr);
    // list1.push_back(g);
//     ShuntingYard h  (" - ( - 6 * - 2)",nullptr);
//    list1.push_back(h);
//    ShuntingYard i(" 0.2 * 0.5 ", nullptr);
//    cout << i.calculate() << endl;
//     ShuntingYard i1  (" (0.8 -(0.2 * 0.5) + 0.8 ) / 0.5 ",nullptr);
//    list1.push_back(i1);
//    ShuntingYard i2(" 1/3 ", nullptr);
//    cout << i2.calculate() << endl;
//    ShuntingYard i3(" 1 / 3 / 1 / 4 / 1 / 5", nullptr);
//    cout << i3.calculate() << endl;
//     ShuntingYard i4  (" (1 / 3)* (1 / 4) * (1 / 5) ",nullptr);
    //list1.push_back(i4);


//    for ( ShuntingYard e : list1){
//        cout<< e.calculate()<<endl;
//    }
    //  cout<<s.calculate()<<endl;
    //ReadData x;
    /*
    x.lexer("data",nullptr);


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