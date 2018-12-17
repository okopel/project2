

#include <string>
#include "ShuntingYard.h"

bool ShuntingYard::isOperator(char c) {
    return (c == '+' || c == '*' || c == '/' || c == '-');
}

ShuntingYard::ShuntingYard(string s) {
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
                this->stack.push("" + c);
            } else if (c == '(') { //start of expression case
                this->stack.push(to_string(c));
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
    //todo calculating and vars are in:
    this->c->getFromSymbolTable("fdkgdfmlgdfg");
}
