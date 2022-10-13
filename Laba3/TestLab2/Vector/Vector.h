//
// Created by yaroslav on 29.9.22.
//

#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include <ostream>
#include "Number.h"
#include "cmath"
// Create .h file at first

class Vector {
private:
    Number x;
    Number y;
public:
    Vector();

    Vector(const Number &x_, const Number &y_);

    Number getX() const;

    Number getY() const;

    void setVector(const Vector &first);

    void setVector(const Number &first, const Number &second);

    void add(const Vector &first);

    void sub(const Vector &first);

    void mul(const Number &first);

    void div(const Number &first);

    Number getRadius();

    Number getAngle();

    friend std::ostream &operator<<(std::ostream &os, const Vector &first);
};

const Vector VECTOR_ZERO = Vector(ZERO, ZERO);
const Vector VECTOR_ONE = Vector(ONE, ONE);

#endif //VECTOR_VECTOR_H
