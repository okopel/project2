#ifndef PROJECT_EXPRESSION_H
#define PROJECT_EXPRESSION_H

#include <string>
#include <iostream>

using namespace std;

class Expression {
protected:
    char operatorType;
public:
    virtual double calculate() = 0;

    char getOperator();
};

class Number : public Expression {
protected:
    double value;
public:
    Number(double value) : value(value) {}

    Number(string values) {

        this->value = stod(values);
    }
    double calculate() override;

};

class UnaryExpression : public Expression {
protected:
    Expression *expression;
public:
    double calculate() override;
};

class openPar:public  UnaryExpression{
public:
    openPar();
};

class ClosePar:public  UnaryExpression{
public:
    ClosePar();
};

class Neg : public UnaryExpression {
public:
    double calculate() override;
};

class BinaryExpression : public Expression {
protected:
    Expression *left;
    Expression *Right;
public:
    double calculate() = 0;

    BinaryExpression(Expression *left, Expression *Right) : left(left), Right(Right) {};
};

class Plus : public BinaryExpression {
public:
    Plus(Expression* l, Expression* r);

    double calculate() override;
};

class Minus : public BinaryExpression {
public:
    Minus(Expression* l, Expression* r);

    double calculate() override;
};


class Mul : public BinaryExpression {
public:
    Mul(Expression* l, Expression* r);

    double calculate() override;
};

class Div : public BinaryExpression {
public:
    Div(Expression* l, Expression* r);

    double calculate() override;
};

class BoolExpression : public BinaryExpression {
public:
    BoolExpression(Expression *l, Expression *r);

    double calculate() override;
};

#endif //PROJECT_EXPRESSION_H
