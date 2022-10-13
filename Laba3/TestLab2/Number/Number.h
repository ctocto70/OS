//
// Created by yaroslav on 29.9.22.
//

#ifndef NUMBER_NUMBER_H
#define NUMBER_NUMBER_H

#include <ostream>

class Number {
private:
    double value;
public:
    Number();

    Number(const double &value);

    double toInt() const;

    void setNumber(const double &newValue);

    void setNumber(const Number &newValue);

    friend Number &operator+(const Number &first, const Number &second);

    friend Number &operator-(const Number &first, const Number &second);

    friend Number &operator*(const Number &first, const Number &second);

    friend Number &operator/(const Number &first, const Number &second);

    Number &operator+=(const Number &first);

    Number &operator-=(const Number &first);

    Number &operator*=(const Number &first);

    Number &operator/=(const Number &first);

    Number &operator=(const Number &first);

    friend std::ostream &operator<<(std::ostream &os, const Number &first);
};

bool operator==(const Number &first, const Number &second);

const Number createNumber(const double &value_);

const Number ZERO = Number(0);
const Number ONE = Number(1);
#endif //NUMBER_NUMBER_H
