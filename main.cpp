#include <iostream>
#include "ReadData.h"
#include "ShuntingYard.h"
#include <list>

int main(int argc, char **argv) {

    ReadData x;
    x.lexer("data");
    x.parser();


    return 0;
}