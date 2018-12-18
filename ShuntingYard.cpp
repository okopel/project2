

#include <string>
#include "ShuntingYard.h"

bool ShuntingYard::isOperator(char c) {
    return (c == '+' || c == '*' || c == '/' || c == '-');
}

ShuntingYard::ShuntingYard(string s, Command *com) : ComExp(com) {
    string buffer;
    for (char c:s) {
        //disregard from spaces
        if (c == ' ') {
            continue;
        }
        //number case
        if (isdigit(c)) {
            buffer += c;
        } else {
            if (!buffer.empty()) {
                this->queue.push(buffer);
                buffer = "";
            } //operator case
            if (this->isOperator(c)) {
                string top;
                if (!this->stack.empty()) {
                    top = this->stack.top();
                    while ((!this->stack.empty()) && (top == "*" || top == "/") && (top != "(") && (c != '*') &&
                           (c != '/')) {
                        this->queue.push(top);
                        this->stack.pop();
                    }
                }
                this->stack.push(this->charToString(c));
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
    //move to the queue
    while (!this->stack.empty()) {
        this->queue.push(this->stack.top());
        this->stack.pop();
    }
}

double ShuntingYard::calculate() {
    double result;
    double tmpNum;
    Expression *e;
    vector<string> vecOfQueue;
    while (!queue.empty()) {
        string s = queue.front();
        if ((!isOperator(s[0])) && (!isNumber(s))) { //not num and not operator->var
            s = to_string(this->c->getFromSymbolTable(s));
        }
        vecOfQueue.push_back(s);
        queue.pop();
    }

    return this->calExp(vecOfQueue);

}

bool ShuntingYard::isNumber(string s) {
    for (char c:s) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

double ShuntingYard::calExp(vector<string> v) {


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
