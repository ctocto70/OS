// MathLibrary.cpp
// compile with: cl /c /EHsc MathLibrary.cpp
// post-build command: lib MathLibrary.obj

#include "Number.h"
Number :: Number() : value(0) {};

Number :: Number(const double& value_) : value(value_) {}; 

double Number ::	toInt() const {
	return value;
}

void Number::setNumber(const double& newValue) {
	value = newValue;
}

void Number::setNumber(const Number& newValue) {
	value = newValue.toInt();
}

Number& operator+(const Number& first, const Number& second) {
	Number sum = Number(first.toInt() + second.toInt());
	return sum;
}

Number& operator-(const Number& first, const Number& second) {
	Number sum = Number(first.toInt() - second.toInt());
	return sum;
}

Number& operator*(const Number& first, const Number& second) {
	Number sum = Number(first.toInt() * second.toInt());
	return sum;
}

Number& operator/(const Number& first, const Number& second) {
	Number sum = Number(first.toInt() / second.toInt());
	return sum;
}

Number& Number::operator+=(const Number& first) {
	this->value += first.toInt();
	return *this;
}

Number& Number::operator-=(const Number& first) {
	this->value -= first.toInt();
	return *this;
}

Number& Number::operator*=(const Number& first) {
	this->value *= first.toInt();
	return *this;
}

Number& Number::operator/=(const Number& first) {
	this->value /= first.toInt();
	return *this;
}

Number& Number::operator=(const Number& first) {
	value = first.toInt();
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Number& first) {
	os << first.toInt();
	return os;
}

bool operator==(const Number& first, const Number& second)
{
	return (first.toInt() == second.toInt());
}

const Number& createNumber(const double& value_) {
	return Number(value_);
}



