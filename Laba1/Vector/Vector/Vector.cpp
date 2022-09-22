#include "pch.h"
#include <utility>
#include "Vector.h"
#include "Number.h"

int sum(int a, int b) {
	Number number();
	return a + b;
}

Vector::Vector() {
	x = ZERO;
	y = ZERO;
}

Vector::Vector(const Number& x_, const Number& y_) {
	x = x_;
	y = y_;
}

Number Vector::getX() const {
	return x;
}

Number Vector::getY() const  {
	return y;
}

void Vector::setVector(const Vector& first) {
	x = first.getX();
	y = first.getY();
}
void Vector::setVector(const Number& first, const Number& second) {
	x = first;
	y = second;
}

void Vector::add(const Vector& first) {
	this->x += first.getX();
	this->y += first.getY();
}

void VECTOR_API Vector::sub(const Vector& first) {
	this->x -= first.getX();
	this->y -= first.getY();
}

void VECTOR_API Vector::mul(const Number& first) {
	this->x *= first;
	this->y *= first;
}

void VECTOR_API Vector::div(const Number& first) {
	this->x /= first;
	this->y /= first;
}

Vector Vector::sum(const Vector& first, const Vector& second) {
	return Vector(first.getX() + second.getX(), first.getY() + second.getY());
}

Vector Vector::sub(const Vector& first, const Vector& second) {
	return Vector(first.getX() - second.getX(), first.getY() - second.getY());
}

Number Vector::getRadius() {
	return createNumber(std::sqrt((x * x + y * y).toInt()));
}
Number Vector::getAngle() {
	return createNumber(std::atan((x / getRadius()).toInt()));
}

std::ostream& operator<<(std::ostream& os, const Vector& first) {
	os << first.getX() << " " << first.getY();
	return os;
}