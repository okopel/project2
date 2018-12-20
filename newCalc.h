

#ifndef PROJECT_NEWCALC_H
#define PROJECT_NEWCALC_H


#include <queue>
#include <stack>
#include "Expression.h"
#include "ComExp.h"

class newCalc : public ComExp {
protected:
    queue<Expression> q;
    stack<string> s;

    bool isLetter(char c);

public:
    newCalc(string s, Command *com);

};


#endif //PROJECT_NEWCALC_H
