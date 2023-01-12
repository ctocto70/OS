//
// Created by yarov on 13.10.2022.
//

#ifndef LAB4_MATRIXMULTIPLY_H
#define LAB4_MATRIXMULTIPLY_H

#include "Vector.h"
#include <thread>
#include <cmath>
#include <algorithm>
#include "BufferedChannel.h"

class MatrixMultiply {
public:
    static void MultiplyBlock(int firstX, int firstY, int secondX, int secondY, int dimension,
                              const std::vector<std::vector<int>> &first,
                              const std::vector<std::vector<int>> &second,
                              std::vector<std::vector<int>> &result);

    static void MultiplyMatrix(const std::vector<std::vector<int>> &first,
                               const std::vector<std::vector<int>> &second,
                               std::vector<std::vector<int>> &result);

    static void
    MultiplyBlockChannel(BufferedChannel<std::pair<std::pair<int, int>, std::pair<int, int>>>& channel, int dimension,
                         const Vector &first,
                         const Vector &second,
                         Vector &result);

    static void MultiplyMatrixChannel(const Vector &first, const Vector &second, Vector &result, int dimension);

    static std::thread *PushTask(int firstX, int firstY, int secondX, int secondY,
                          BufferedChannel<std::pair<std::pair<int, int>, std::pair<int, int>>> &channel);

    static void
    MultiplyBlockThread(int firstX, int firstY, int secondX, int secondY, int dimension, const Vector &first,
                        const Vector &second,
                        Vector &result);

    static void MultiplyMatrixThread(const Vector &first, const Vector &second, Vector &result, int dimension);

    static void MultiplyAll(int matrixSize);

    static void MultiplyAllWithChannel(int matrixSize);
};

#endif //LAB4_MATRIXMULTIPLY_H
