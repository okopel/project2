/*****************************
 * Project of:
 * Ori Kopel 205533151
 * Shlomo Rabinovich 308432517
 * December 18
 ******************************/

#ifndef PROJECT_EXPRESSION_H
#define PROJECT_EXPRESSION_H

#include <string>
#include <iostream>

using namespace std;

/**
 * Expression class
 */
class Expression {
protected:
    char operatorType;
public:
    /**
     * calculate expression value
     * @return value
     */
    virtual double calculate() = 0;

    /**
     * @return operator
     */
    char getOperator();

};

/**
 * Number
 */
class Number : public Expression {
protected:
    double value;
public:
    explicit Number(double value) : value(value) {}

    explicit Number(const string &values);

    double calculate() override;

};

/*
 *Unary Exp class
 */
class UnaryExpression : public Expression {
protected:
    Expression *expression;
public:
    double calculate() override;
};

/**
 * open parenthesis class
 */
class openPar : public UnaryExpression {
public:
    openPar();
};

/**
 * close parenthesis class
 */
class ClosePar : public UnaryExpression {
public:
    ClosePar();
};

/**
 * Neg class
 */
class Neg : public UnaryExpression {
public:
    double calculate() override;
};

/**
 * Binary Expresion
 */
class BinaryExpression : public Expression {
protected:
    Expression *left;
    Expression *Right;
public:
    double calculate() = 0;

    virtual ~BinaryExpression() {
        delete this->left;
        delete this->Right;
    }

    BinaryExpression(Expression *left, Expression *Right) : left(left), Right(Right) {};
};

/**
 * Plus
 */
class Plus : public BinaryExpression {
public:
    Plus(Expression *l, Expression *r);

    double calculate() override;
};

/**
 * Minus
 */
class Minus : public BinaryExpression {
public:
    Minus(Expression *l, Expression *r);

    double calculate() override;
};

/**
 * Multiply
 */
class Mul : public BinaryExpression {
public:
    Mul(Expression *l, Expression *r);

    double calculate() override;
};

/**
 * Division
 */
class Div : public BinaryExpression {
public:
    Div(Expression *l, Expression *r);

    double calculate() override;
};

/**
 * Bollean expression
 */
class BoolExpression : public BinaryExpression {

public:
    BoolExpression(Expression *l, Expression *r);

    double calculate() override;
};

#endif //PROJECT_EXPRESSION_H
