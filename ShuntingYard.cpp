/*****************************
 * Project of:
 * Ori Kopel 205533151
 * Shlomo Rabinovich 308432517
 * December 18
 ******************************/

#include <iostream>
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
    return priF >= priL;
}

ShuntingYard::ShuntingYard(string s, Command *com) {
    if (s.empty()) {
        return;
    }
    s = arrangeString(s);
    this->command = com;
    string buffer;
    string varBuf;
    for (char c:s) {
        //disregard from spaces
        if (c == ' ') {
            continue;
        }
        //number case
        if ((isdigit(c) || c == '.') && varBuf.empty()) {
            buffer += c;
            continue;
        }
        if ((isLetter(c) || (c == '_')) || (isdigit(c))) {
            varBuf += c;
            continue;
        } else {
            if (!varBuf.empty()) {
                string tmp = to_string(this->command->getFromSymbolTable(varBuf));
                if (tmp[0] == '-') {
                    this->stack.push("-");
                    tmp = tmp.substr(1, tmp.size() - 1);
                }
                this->queue.push(tmp);
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
                    while ((!this->stack.empty()) && pri && top[0] != '(') {
                        pri = this->priority(top[0], c);
                        this->queue.push(this->stack.top());
                        this->stack.pop();
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
                //this->queue.push(p);//add the ')'
            }

        }
    }//end for of string s
    if (!buffer.empty()) {
        this->stack.push(buffer);
    }
    if (!varBuf.empty()) {
        string tmp = to_string(this->command->getFromSymbolTable(varBuf));
        if (tmp[0] == '-') {
            this->stack.push("-");
            tmp = tmp.substr(1, tmp.size() - 1);
        }
        this->queue.push(tmp);
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
            Expression *number = new Number(queue.front());
            nums.push(number);
        } else if (isOperator(queue.front()[0])) {
            Expression *e1 = new Number(0);
            if (!nums.empty()) {
                delete e1;
                e1 = nums.top();
                nums.pop();
            }
            Expression *e2 = new Number(0);
            if (!nums.empty()) {
                delete e2;
                e2 = nums.top();
                nums.pop();
            }
            nums.push(this->calExp(queue.front()[0], e2, e1));
            delete e1;
            delete e2;

        }
        queue.pop();
    }
    Expression *result = nums.top();
    double res = result->calculate();

    while (!nums.empty()) {
        Expression *e = nums.top();
        nums.pop();
        delete e;
    }
    return res;
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
        default:
            return nullptr;

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

string ShuntingYard::arrangeString(string s) {
    string res;
    for (char c:s) {
        if (c != ' ') {
            res += c;
        }
    }
    s = "";
    if (res[0] == '-') {
        s = "0";
    }
    s += res;
    for (unsigned int i = 0; i < s.length() - 1; i++) {
        if ((s[i] == '-' && s[i + 1] == '-') || ((s[i] == '+' && s[i + 1] == '+'))) {
            s[i] = '+';
            s[i + 1] = ' ';
            i = 0;
        }
        if ((s[i] == '-' && s[i + 1] == '+') || ((s[i] == '+' && s[i + 1] == '-'))) {
            s[i] = '-';
            s[i + 1] = ' ';
            i = 0;
        }
        if (s[i] == '*' && s[i + 1] == '+') {
            s[i] = '*';
            s[i + 1] = ' ';
            i = 0;
        }
        if (s[i] == '/' && s[i + 1] == '+') {
            s[i] = '/';
            s[i + 1] = ' ';
            i = 0;
        }
    }
    res = "";
    for (char c:s) {
        if (c != ' ') {
            res += c;
        }
    }
    s = res;
    return s;
}
