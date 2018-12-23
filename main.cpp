#include <iostream>
#include "ReadData.h"
#include "ShuntingYard.h"
#include <list>

int main(int argc, char **argv) {


    /*  ShuntingYard e("5 - + - 3", nullptr);
      cout << e.calculate()<<"="<< 5 - + - 3<< endl;
      ShuntingYard e0("5 + - + 3", nullptr);
      cout << e0.calculate()<<"="<< 5 + - + 3<< endl;
      ShuntingYard e1("5 - - 3", nullptr);
      cout << e1.calculate()<<"="<< 5 - - 3<< endl;
      ShuntingYard e2("3 - + 10", nullptr);
      cout << e2.calculate()<<"="<<3 - + 10 << endl;
      ShuntingYard e22("3 + - 10", nullptr);
     // cout << e22.calculate()<<"="<<3 + - 10 << endl;
      ShuntingYard e3("3 * - 10", nullptr);
      cout << e3.calculate()<<"="<< 3 * - 10<< endl;
      ShuntingYard e31("3 * + 10", nullptr);
      cout << e31.calculate()<<"="<< 3 * + 10<< endl;
      ShuntingYard e32("81 / - 9", nullptr);
     // cout << e32.calculate()<<"="<< 81 / - 9<< endl;
      ShuntingYard e33("81 / + 9", nullptr);
    //  cout << e33.calculate()<<"="<< 81 / + 9<< endl;





      ShuntingYard i2(" 1/3 ", nullptr);
      //cout << i2.calculate()<<"="<<  1/3<< endl;
      ShuntingYard i3(" 1 / 3 / 1 / 4 / 1 / 5", nullptr);
      //cout << i3.calculate()<<"="<<  1 / 3 / 1 / 4 / 1 / 5<< endl;
      ShuntingYard i4(" (1 / 3)* (1 / 4) * (1 / 5) ", nullptr);
     // cout << i4.calculate()<<"="<< (1 / 3)* (1 / 4) * (1 / 5)<< endl;

      ShuntingYard f(" - ( - 2 + 4)", nullptr);
      cout << f.calculate()<<"="<<- ( - 2 + 4) << endl;
      ShuntingYard g(" - ( - 6 / - 2)", nullptr);
      cout << g.calculate()<<"="<<  - ( - 6 / - 2)<< endl;
      ShuntingYard h(" - ( - 6 * - 2)", nullptr);
      cout << h.calculate()<<"="<< - ( - 6 * - 2)<< endl;
      ShuntingYard i1(" (0.8 -(0.2 * 0.5) + 0.8 ) / 0.5 ", nullptr);
      cout << i1.calculate()<<"="<< (0.8 -(0.2 * 0.5) + 0.8 ) / 0.5 << endl;*/

    ReadData x;

    x.lexer("data");
    x.parser();

//    int y;
//    cin >> y;
//    return 0;
}