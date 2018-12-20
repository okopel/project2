
#include <iostream>

#include <string>
#include "ShuntingYard.h"

using namespace std;

bool ShuntingYard::isOperator(char c) {
    return (c == '+' || c == '*' || c == '/' || c == '-');
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
                    while ((!this->stack.empty()) && (top == "*" || top == "/") && (top != "(") &&
                           (c != '*') && (c != '/')) {
                        this->queue.push(top);
                        this->stack.pop();
                    }
                    this->stack.push(this->charToString(c));
                } else { this->stack.push(this->charToString(c)); }
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
    /* vector<string> vec;
     while (!this->queue.empty()) {
         vec.push_back(this->queue.front());
         this->queue.pop();
     }
     //now the queue is vector
     if (vec.size() == 1) {
         return stoi(vec[0]);
     }*/


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

    /*
    for (int i = 0; i < vec.size(); i++) {
        if (isNumber(vec[i])) {
            nums.push(new Number(vec[i]));
        } else if (isOperator(vec[i][0])) {
            Expression *e1 = nums.top();
            nums.pop();
            Expression *e2 = nums.top();
            nums.pop();
            nums.push(this->calExp(vec[i][0], e1, e2));
        }
    }*/

    return 0;
    /*
    int index = 0;
    Expression *exp1 = new Number(vec[0]);
    Expression *exp2;
    while (index < (vec.size()-1)) {
        exp2 = new Number(vec[++index]);
        index++;

        if (vec[index] == "*") {
            exp1 = new Number((Mul(exp1, exp2)).calculate());
        } else if (vec[index] == "+") {
            exp1 = new Number(Plus(exp1, exp2).calculate());
        } else if (vec[index] == "-") {
            exp1 = new Number(Minus(exp1, exp2).calculate());
        } else if (vec[index] == "/") {
            exp1 = new Number(Div(exp1, exp2).calculate());
        } else if ((vec[index] == "(") || (vec[index] == ")")) {
            index++;
            continue;
        }
    }
*/

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
