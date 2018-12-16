#ifndef PROJECT_SHUNTINGYARD_H
#define PROJECT_SHUNTINGYARD_H

#include <queue>
#include <stack>
#include <string>
#include "Expression.h"

using namespace std;

class ShuntingYard {
private:
    queue<string> queee;
    stack<string> stack;
public:
    /**
     *
     * @param s is the input (2+3-3*5)
     */
    ShuntingYard(string s) {
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
                    this->queee.push(buffer);
                    buffer = "";
                }
                if (c == '(') { //start of expression
                    this->stack.push(to_string(c));
                } else if (c == ')') { //end of expression
                    string p = this->stack.pop();
                    while (p != "(") {
                        this->queee.push(p);
                        p = this->stack.pop();
                    }
                } else if (c == '+' || c == '*' || c == '/' || c == '-') {

                }

            }
        }//end for of string s
    }
};


#endif //PROJECT_SHUNTINGYARD_H
