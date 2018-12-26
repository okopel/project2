/*****************************
 * Project of:
 * Ori Kopel 205533151
 * Shlomo Rabinovich 308432517
 * December 18
 ******************************/
#include "Expression.h"

double Number::calculate() {
    return this->value;
}

Number::Number(const string &values) {
    this->value = stod(values);
}

double Plus::calculate() {
    return this->left->calculate() + this->Right->calculate();
}

Plus::Plus(Expression *l, Expression *r) : BinaryExpression(l, r) {
    this->operatorType = '+';
}

Minus::Minus(Expression *l, Expression *r) : BinaryExpression(l, r) {
    this->operatorType = '-';
}

Mul::Mul(Expression *l, Expression *r) : BinaryExpression(l, r) {
    this->operatorType = '*';
}

Div::Div(Expression *l, Expression *r) : BinaryExpression(l, r) {
    this->operatorType = '/';
}

double Minus::calculate() {
    return this->left->calculate() - this->Right->calculate();
}

double Div::calculate() {
    return this->left->calculate() / this->Right->calculate();
}

double Mul::calculate() {
    return this->left->calculate() * this->Right->calculate();
}

double UnaryExpression::calculate() {
    return 0;
}

double Neg::calculate() {
    return -this->expression->calculate();
}

char Expression::getOperator() {
    return this->operatorType;
}


openPar::openPar() {
    this->operatorType = '(';
}

ClosePar::ClosePar() {
    this->operatorType = ')';

}

/**
 * calc rigt & left expressions
 * @return
 */
double BoolExpression::calculate() {
    double r = this->Right->calculate();
    double l = this->left->calculate();

}

BoolExpression::BoolExpression(Expression *l, Expression *r) : BinaryExpression(l, r) {

}
