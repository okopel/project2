//
// Created by okoprl on 12/19/18.
//

#ifndef PROJECT_CALCULATOR_H
#define PROJECT_CALCULATOR_H


#include <queue>
#include <stack>
#include <string>
#include "Expression.h"
#include "ComExp.h"

using namespace std;

class Calculator : public ComExp {
private:
    std::queue<Expression> queue;
    std::stack<Expression> stack;

    bool isNumber(string s);
    bool isLetter(char c);
    bool isOperator(char c);

    double calExp(vector<Expression> v);

    string charToString(char c);

    Expression* charToExp(char c);

public:
    /**
     *
     * @param s is the input (2+3-3*5)
     * note that the function get numbers, vars already convercted in the parser
     */
    Calculator(string s, Command *com);

    double calculate() override;
};


#endif //PROJECT_CALCULATOR_H
