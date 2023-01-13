#pragma once

#include "Vector.h"
#include <windows.h>
#include <cmath>
#include <algorithm>

class MatrixMultiply {
public:
    static void MultiplyBlock(int firstX, int firstY, int secondX, int secondY, int dimension,
        const std::vector<std::vector<int>>& first,
        const std::vector<std::vector<int>>& second,
        std::vector<std::vector<int>>& result);

    static void MultiplyMatrix(const std::vector<std::vector<int>>& first,
        const std::vector<std::vector<int>>& second,
        std::vector<std::vector<int>>& result);

    static void
        MultiplyBlockThread(int firstX, int firstY, int secondX, int secondY, int dimension, const Vector& first,
            const Vector& second,
            Vector& result);

    static void MultiplyMatrixThread(const Vector& first, const Vector& second, Vector& result, int dimension);

    static void MultiplyAll(int matrixSize);

    struct Args {
        Args(int firstX_, int firstY_, int secondX_, int secondY_, int dimension_,
            const Vector& first_, const Vector& second_,
            Vector& result_)
            : firstX(firstX_), firstY(firstY_), secondX(secondX_), secondY(secondY_), 
            dimension(dimension_), first(first_), second(second_), result(result_) {}
        int firstX;
        int firstY;
        int secondX;
        int secondY;
        int dimension;
        const Vector& first;
        const Vector& second;
        Vector& result;
    };

    static DWORD WINAPI Call(LPVOID args) {
        Args* castedArgs = (Args*)args;
        MultiplyBlockThread(castedArgs -> firstX, castedArgs -> firstY, castedArgs->secondX,
            castedArgs-> secondY, castedArgs-> dimension, castedArgs-> first,
            castedArgs-> second,
            castedArgs-> result);
        ExitThread(0);
    }
};