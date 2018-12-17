#include "Expression.h"

double Number::calculate() {
    return this->value;
}

double Plus::calculate() {
    return this->left->calculate() + this->Right->calculate();
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
