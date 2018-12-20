#include <iostream>
#include "ReadData.h"
#include "ShuntingYard.h"
#include "text.h"
#include <list>

int main() {

    ReadData x;
    x.lexer("data");
    x.parser();


    return 0;
}