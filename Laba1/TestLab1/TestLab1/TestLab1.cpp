// TestLab1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Vector.h"
#include "Number.h"

int main()
{
    Number number = ZERO;
    for (int i = 0; i < 100; i++) {
        number += createNumber(i);
    }
    std::cout << number << " " << 50 * 99 << "\n";
    for (int i = 0; i < 100; i++) {
        number -= createNumber(i);
    }
    std::cout << number << " " << 0 << "\n";
    number = ONE;
    for (int i = 1; i <= 10; i++) {
        number /= createNumber(i);
    }
    std::cout << number << "\n";
    for (int i = 1; i <= 10; i++) {
        number *= createNumber(i);
    }
    std::cout << number << " " << 1 << "\n";

    Vector vector = VECTOR_ZERO;
    for (int i = 0; i < 100; i++) {
        vector.add(VECTOR_ONE);
    }
    std::cout << vector << "\n";
    for (int i = 0; i < 100; i++) {
        vector.setVector(Vector::sub(vector, VECTOR_ONE));
    }
    std::cout << vector << "\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
