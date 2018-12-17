#ifndef PROJECT_EXPRESSION_H
#define PROJECT_EXPRESSION_H

class Expression {

public:
    virtual double calculate() = 0;

};

class Number : public Expression {
protected:
    double value;
public:
    Number(double value) : value(value) {}

    double calculate() override;

};

class UnaryExpression : public Expression {
protected:
    Expression *expression;
public:
    double calculate() override;
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
    double calculate() override;
};

class Minus : public BinaryExpression {
public:
    double calculate() override;
};


class Mul : public BinaryExpression {
public:
    double calculate() override;
};

class Div : public BinaryExpression {
public:
    double calculate() override;
};


#endif //PROJECT_EXPRESSION_H
