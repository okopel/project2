#ifndef PROJECT_SHUNTINGYARD_H
#define PROJECT_SHUNTINGYARD_H

#include <queue>
#include <stack>
#include <string>
#include "Expression.h"

using namespace std;

class ShuntingYard {
private:
    std::queue<string> queue;
    std::stack<string> stack;

    bool isOperator(char c);

public:
    /**
     *
     * @param s is the input (2+3-3*5)
     * note that the function get numbers, vars already convercted in the parser
     */
    ShuntingYard(string s);
};


#endif //PROJECT_SHUNTINGYARD_H
