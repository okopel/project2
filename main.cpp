#include <iostream>
#include "ReadData.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    ReadData x;
    x.lexer("data");
    x.parser();


    for (auto &s : x.getVector()) {
        cout << s;
    }
    return 0;
}