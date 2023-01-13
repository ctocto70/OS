#include <iostream>
#include <ctime>
#include "Vector.h"
#include "MatrixMultiply.h"
int main() {
    srand(time(0));
    MatrixMultiply::MultiplyAll(100);
}
