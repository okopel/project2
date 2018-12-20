//
// Created by okoprl on 12/19/18.
//
/*
#include "Calculator.h"

#include <iostream>

#include <string>
#include "ShuntingYard.h"

using namespace std;

bool Calculator::isOperator(char c) {
    return (c == '+' || c == '*' || c == '/' || c == '-');
}

Calculator::Calculator(string s, Command *com) : ComExp(com) {
    string buffer;
    string varBuf;
    for (char c:s) {
        //disregard from spaces
        if (c == ' ') {
            continue;
        }
        if (isLetter(c)) {
            varBuf += c;
            continue;
        }
        //number case
        if (isdigit(c)) {
            buffer += c;
            continue;
        } else {
            if (!varBuf.empty()) {
                this->queue.push(Number(this->c->getFromSymbolTable(varBuf)));
                varBuf = "";
            }
            if (!buffer.empty()) {
                this->queue.push(Number(buffer));
                buffer = "";
            } //operator case
            if (this->isOperator(c)) {
                Expression *top;
                if (!this->stack.empty()) {
                    top = &(this->stack.top());

                    while ((!this->stack.empty()) && (top->getOperator() == '*' || top->getOperator() == '/') &&
                           (top->getOperator() != '(') && (c != '*') && (c != '/')) {
                        this->queue.push(*top);
                        this->stack.pop();
                    }
                }
                this->stack.push(this->charToExp(c));
            } else if (c == '(') { //start of expression case
                this->stack.push(this->charToExp(c));
            } else if (c == ')') { //end of expression case
                Expression *p = &this->stack.top();
                this->stack.pop();
                while (p->getOperator() != '(') {
                    this->queue.push(*p);
                    p = &this->stack.top();
                    this->stack.pop();
                }
                this->queue.push(*p);//add the ')'
            }
        }
    }//end for of string s
    if (!buffer.empty()) {
        this->stack.push(Number(buffer));
    }
    //move to the queue
    while (!this->stack.empty()) {
        this->queue.push(this->stack.top());
        this->stack.pop();
    }

}

double Calculator::calculate() {
    double result;
    double tmpNum;
    Expression *e;
    vector<string> vecOfQueue;
    while (!queue.empty()) {
        Expression *s = &queue.front();
        if ((!isOperator(s)) && (!isNumber(s))) { //not num and not operator->var
            s = to_string(this->c->getFromSymbolTable(s));
        }
        vecOfQueue.push_back(s);
        queue.pop();
    }

    return this->calExp(vecOfQueue);

}

bool Calculator::isNumber(string s) {
    for (char c:s) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

double Calculator::calExp(vector<string> v) {
    int index = v.size() - 1;
    double result;
    char c = v[index][0];

    switch (c) {
        case '+':
    }


}

string Calculator::charToString(char c) {
    switch (c) {
        case '+':
            return "+";
        case '-':
            return "-";
        case '*':
            return "*";
        case '/':
            return "/";
        case '(':
            return "(";
        case ')':
            return ")";
        default:
            return "";
    }
}

Expression* Calculator::charToExp(char c) {
    switch (c) {
        case '+':
            return Plus();
        case '-':
            return Minus();
        case '*':
            return Mul();
        case '/':
            return Div();
        case '(':
            return openPar();
        case ')':
            return ClosePar();
        default:
            return nullptr;
    }
}

bool Calculator::isLetter(char c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));

}
*/