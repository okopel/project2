

#ifndef PROJECT_COMEXP_H
#define PROJECT_COMEXP_H

#include "Expression.h"
#include "Command.h"

class ComExp : public Expression {
protected:
    Command *c;
public:
    ComExp(Command *c);
    virtual double calculate() = 0;
};


#endif //PROJECT_COMEXP_H
