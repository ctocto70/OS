//
// Created by yaroslav on 13.1.23.
//

#include "MatrixMultiply.h"

void MatrixMultiply::MultiplyBlock(int firstX, int firstY, int secondX, int secondY, int dimension,
                                   const std::vector<std::vector<int>> &first,
                                   const std::vector<std::vector<int>> &second,
                                   std::vector<std::vector<int>> &result) {
    for (int i = firstX; i < firstX + dimension && i < first.size(); i++) {
        for (int j = secondY; j < secondY + dimension && j < second.size(); j++) {
            for (int l = firstY, m = secondX;
                 (l < firstY + dimension && l < first.size()) &&
                 (m < secondX + dimension && m < second.size()); l++, m++) {
                result[i][j] += first[i][l] * second[m][j];
            }
        }
    }
}

void MatrixMultiply::MultiplyMatrix(const std::vector<std::vector<int>> &first,
                                    const std::vector<std::vector<int>> &second,
                                    std::vector<std::vector<int>> &result) {
    result.clear();
    for (int i = 0; i < first.size(); i++) {
        std::vector<int> vec;
        for (int j = 0; j < first.size(); j++) {
            vec.push_back(0);
        }
        result.push_back(vec);
    }
    MultiplyBlock(0, 0, 0, 0, first.size(), first, second, result);
}

void
MatrixMultiply::MultiplyBlockThread(int firstX, int firstY, int secondX, int secondY, int dimension,
                                    const Vector &first, const Vector &second,
                                    Vector &result) {
    for (int i = firstX; i < firstX + dimension && i < first.size(); i++) {
        for (int j = secondY; j < secondY + dimension && j < second.size(); j++) {
            for (int l = firstY, m = secondX;
                 (l < firstY + dimension && l < first.size()) &&
                 (m < secondX + dimension && m < second.size()); l++, m++) {
                result.add(i, j, first.get(i, l) * second.get(m, j));
            }
        }
    }
}

void MatrixMultiply::MultiplyMatrixThread(const Vector &first, const Vector &second, Vector &result, int dimension) {
    result.zeros(first.size());
    int currentThreadIndex = 0;
    int rangeI = std::ceil(first.size() / (double) dimension);
    int rangeJ = std::ceil(second.size() / (double) dimension);
    int rangeK = std::ceil(result.size() / (double) dimension);
    std::vector<pthread_t> threads(rangeI * rangeJ * rangeK);
    pthread_attr_t attr;

    for (int i = 0; i < std::ceil(first.size() / (double) dimension); i++) {
        for (int j = 0; j < std::ceil(second.size() / (double) dimension); j++) {
            for (int l = 0; l < std::ceil(result.size() / (double) dimension); l++) {
                pthread_create(&threads[currentThreadIndex++], NULL, MatrixMultiply::Call,
                               new Args(i * dimension, l * dimension, l * dimension, j * dimension,
                                        dimension,
                                        first, second, result));
            }
        }
    }

    for (pthread_t &thread: threads) {
        pthread_join(thread, NULL);
    }
}

void MatrixMultiply::MultiplyAll(int matrixSize) {
    Vector first(matrixSize, true);
    Vector second(matrixSize, true);
    Vector result(matrixSize);

    std::vector<std::vector<int>> firstVector;
    std::vector<std::vector<int>> secondVector;
    std::vector<std::vector<int>> resultVector;
    first.copyTo(firstVector);
    second.copyTo(secondVector);
    auto start = std::chrono::system_clock::now();
    MultiplyMatrix(firstVector, secondVector, resultVector);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Time: " << elapsed_seconds.count() << ", No threads, No block size" << '\n' << '\n';

    for (int i = matrixSize; i >= 1; i--) {
        start = std::chrono::system_clock::now();
        MultiplyMatrixThread(first, second, result, i);
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;
        std::cout << "Time: " << elapsed_seconds.count() << ", Number of threads: "
                  << pow(std::ceil(matrixSize / (double) i), 3)
                  << ", Block size: " << i << '\n';
        std::cout << '\n';
    }
}