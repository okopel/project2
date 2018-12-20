
#include <iostream>

#include <string>
#include "ShuntingYard.h"

using namespace std;

bool ShuntingYard::isOperator(char c) {
    return (c == '+' || c == '*' || c == '/' || c == '-');
}

bool ShuntingYard::priority(char f, char l) {
    int priF = 0, priL = 0;
    if (f == '*' || f == '/') {
        priF = 5;
    }
    if (l == '*' || l == '/') {
        priL = 5;
    }
    return priF > priL;
}

ShuntingYard::ShuntingYard(string s, Command *com) : ComExp(com) {
    string buffer;
    string varBuf;
    for (char c:s) {
        //disregard from spaces
        if (c == ' ') {
            continue;
        }
        //number case
        if (isdigit(c) || c == '.') {
            buffer += c;
            continue;
        }
        if (isLetter(c)) {
            varBuf += c;
            continue;
        } else {
            if (!varBuf.empty()) {
                this->queue.push(to_string(this->c->getFromSymbolTable(varBuf)));
                varBuf = "";
            }
            if (!buffer.empty()) {
                this->queue.push(buffer);
                buffer = "";
            } //operator case
            if (this->isOperator(c)) {
                string top;
                if (!this->stack.empty()) {
                    top = this->stack.top();
                    bool pri = this->priority(top[0], c);
                    if ((!this->stack.empty()) && !pri) {
                        while (!this->stack.empty()) {
                            this->queue.push(top);
                            this->stack.pop();
                        }
                    }
                    this->stack.push(this->charToString(c));
                } else {
                    this->stack.push(this->charToString(c));
                }
            } else if (c == '(') { //start of expression case
                this->stack.push(this->charToString(c));
            } else if (c == ')') { //end of expression case
                string p = this->stack.top();
                this->stack.pop();
                while (p != "(") {
                    this->queue.push(p);
                    p = this->stack.top();
                    this->stack.pop();
                }
                this->queue.push(p);//add the ')'
            }

        }
    }//end for of string s
    if (!buffer.empty()) {
        this->stack.push(buffer);
    }
    if (!varBuf.empty()) {
        this->stack.push(to_string(this->c->getFromSymbolTable(varBuf)));
    }
    //move to the queue
    while (!this->stack.empty()) {
        this->queue.push(this->stack.top());
        this->stack.pop();
    }


}

double ShuntingYard::calculate() {

    ::stack<Expression *> nums;

    while (!this->queue.empty()) {
        if (isNumber(queue.front())) {
            nums.push(new Number(queue.front()));
        } else if (isOperator(queue.front()[0])) {
            Expression *e1 = nums.top();
            nums.pop();
            Expression *e2 = nums.top();
            nums.pop();
            nums.push(this->calExp(queue.front()[0], e2, e1));
        }
        queue.pop();
    }
    Expression *result = nums.top();
    cout << result->calculate() << endl;


    return 0;

}

bool ShuntingYard::isNumber(string s) {
    for (char c:s) {
        if (!isdigit(c) && (c != '.')) {
            return false;
        }
    }
    return true;
}

Expression *ShuntingYard::calExp(char op, Expression *e1, Expression *e2) {
    switch (op) {
        case '+':
            return new Plus(e1, e2);
        case '-':
            return new Minus(e1, e2);
        case '*':
            return new Mul(e1, e2);
        case '/':
            return new Div(e1, e2);

    }


}

string ShuntingYard::charToString(char c) {
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

bool ShuntingYard::isLetter(char c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));

}
