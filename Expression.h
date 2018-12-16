#ifndef PROJECT_EXPRESSION_H
#define PROJECT_EXPRESSION_H

class Expression {
private:

public:
    virtual double calculate();

};

class Number : public Expression {
protected:
    double value;
public:
    Number(double value) : value(value) {}
};

class BinaryExpression : public Expression {
protected:
    Expression left;
    Expression Right;
public:
    BinaryExpression(const Expression &left, const Expression &Right) : left(left), Right(Right) {};
};

class Plus : public BinaryExpression {
public:
    double calculate() override {
        return this->left.calculate() + this->Right.calculate();
    }
};

class Minus : public BinaryExpression {
public:
    double calculate() override;
};

double Minus::calculate() {
    return this->left.calculate() - this->Right.calculate();
}

class Mul : public BinaryExpression {
public:
    double calculate() override;
};

double Mul::calculate() {
    return this->left.calculate() * this->Right.calculate();
}

class Div : public BinaryExpression {
public:
    double calculate() override;
};

double Div::calculate() {
    return this->left.calculate() / this->Right.calculate();
}

#endif //PROJECT_EXPRESSION_H
