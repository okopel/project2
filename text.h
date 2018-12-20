
#ifndef PROJECT_TEXT_H
#define PROJECT_TEXT_H



#include <queue>
#include <stack>
#include <string>
#include "Expression.h"
#include "ComExp.h"

using namespace std;

class text : public ComExp {
private:
    std::queue<string> queue;
    std::stack<string> stack;

    bool isNumber(string s);

    bool isOperator(char c);

    bool isLetter(char c);
    double calc(string op, string s1, string s2);
    double calExp(vector<string> v);

    string charToString(char c);

public:
    /**
     *
     * @param s is the input (2+3-3*5)
     * note that the function get numbers, vars already convercted in the parser
     */
    text(string s, Command *com);

    double calculate() override;
};




#endif //PROJECT_TEXT_H
