

#include "text.h"



#include <iostream>

#include <string>
#include "text.h"

using namespace std;

bool text::isOperator(char c) {
    return (c == '+' || c == '*' || c == '/' || c == '-');
}

text::text(string s, Command *com) : ComExp(com) {
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
                    while ((!this->stack.empty()) && (top == "*" || top == "/") && (top != "(")
                                                                && (c != '*') && (c != '/')) {
                        //this->queue.push(top);
                        //this->stack.pop();
                        string s1=queue.front();
                        queue.pop();
                        string s2=queue.front();
                        queue.pop();
                        this->queue.push(to_string(calc(top,s1,s2)));
                    }

                }
                //this->stack.push(this->charToString(c));
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

    cout<<queue.front()<<endl;
    queue.pop();
    cout<<queue.front()<<endl;
    queue.pop();
    cout<<queue.front()<<endl;


}

double text::calculate() {
    vector<string> vec;
    while (!this->queue.empty()) {
        vec.push_back(this->queue.front());
        this->queue.pop();
    }
    //now the queue is vector
    if (vec.size() == 1) {
        return stoi(vec[0]);
    }

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


}

bool text::isNumber(string s) {
    for (char c:s) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

double text::calExp(vector<string> v) {
    int index = v.size() - 1;
    double result;
    char c = v[index][0];

//        switch (c){
//            case '+':
//                result=new Plus()
    return 0;


}

string text::charToString(char c) {
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

bool text::isLetter(char c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));

}

double text::calc(string op, string s1, string s2) {
    switch (op[0]){
        case '+':
            return stoi(s1)+stoi(s2);
        case '-':
            return stoi(s1)-stoi(s2);
        case '*':
            return stoi(s1)*stoi(s2);
        case '/':
            return stoi(s1)/stoi(s2);
    }
}
