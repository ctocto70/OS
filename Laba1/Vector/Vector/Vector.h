#pragma once

#ifdef VECTOR_EXPORTS
#define VECTOR_API __declspec(dllexport)
#else
#define VECTOR_API __declspec(dllimport)
#endif

#include <ostream>
#include "Number.h"
#include "cmath"

extern "C" VECTOR_API int sum(int a, int b);

// Create .h file at first

extern "C" VECTOR_API class Vector {
private:
	Number x;
	Number y;
public:
	VECTOR_API Vector();
	VECTOR_API Vector(const Number& x_, const Number& y_);
	Number VECTOR_API getX() const;
	Number VECTOR_API getY() const;
	void VECTOR_API setVector(const Vector& first);
	void VECTOR_API setVector(const Number& first, const Number& second);
	void VECTOR_API add(const Vector& first);
	void VECTOR_API sub(const Vector& first);
	void VECTOR_API mul(const Number& first);
	void VECTOR_API div(const Number& first);
	static Vector VECTOR_API sum(const Vector& first, const Vector& second);
	static Vector VECTOR_API sub(const Vector& first, const Vector& second);
	Number VECTOR_API getRadius();
	Number VECTOR_API getAngle();
	friend VECTOR_API std::ostream& operator<<(std::ostream& os, const Vector& first);
}; 

const Vector VECTOR_ZERO = Vector(ZERO, ZERO);
const Vector VECTOR_ONE = Vector(ONE, ONE);


