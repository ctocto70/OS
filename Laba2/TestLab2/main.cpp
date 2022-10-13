#include <iostream>
#include "Number.h"
#include "Vector.h"

int main() {
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
    vector.setVector(VECTOR_ZERO);
    for (int i = 0; i < 100; i++) {
        vector.sub(VECTOR_ONE);
    }
    std::cout << vector << "\n";
    return 0;
}
