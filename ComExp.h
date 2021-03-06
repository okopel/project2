
/*****************************
 * Project of:
 * Ori Kopel 205533151
 * Shlomo Rabinovich 308432517
 * December 18
 ******************************/
#ifndef PROJECT_COMEXP_H
#define PROJECT_COMEXP_H

#include "Expression.h"
#include "Command.h"

/**
 * this class is using Adapter pattern
 * adapt command as expression
 */
class ComExp : public Expression {
protected:
    Command *c;
public:
    explicit ComExp(Command *c);
    virtual double calculate() = 0;
};


#endif //PROJECT_COMEXP_H
