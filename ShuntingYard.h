/*****************************
 * Project of:
 * Ori Kopel 205533151
 * Shlomo Rabinovich 308432517
 * December 18
 ******************************/

#ifndef PROJECT_SHUNTINGYARD_H
#define PROJECT_SHUNTINGYARD_H

#include <queue>
#include <stack>
#include <string>
#include "Expression.h"
#include "Command.h"

using namespace std;

class ShuntingYard : public Expression {
private:
    Command *command;
    std::queue<string> queue;
    std::stack<string> stack;

    bool isNumber(string s);

    bool isOperator(char c);

    bool isLetter(char c);

    bool priority(char f, char l);

    Expression *calExp(char op, Expression *e1, Expression *e2);

    string charToString(char c);

public:
    /**
     *
     * @param s is the input (2+3-3*5)
     * note that the function get numbers, vars already convercted in the parser
     */
    ShuntingYard(string s, Command *com);

    double calculate() override;
};


#endif //PROJECT_SHUNTINGYARD_H
