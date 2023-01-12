//
// Created by yarov on 13.10.2022.
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
MatrixMultiply::MultiplyBlockChannel(BufferedChannel<std::pair<std::pair<int, int>, std::pair<int, int>>> &channel,
                                     int dimension,
                                     const Vector &first,
                                     const Vector &second,
                                     Vector &result) {
    std::pair<std::pair<int, int>, std::pair<int, int>> args = channel.Recv().first;
    int firstX = args.first.first;
    int firstY = args.first.second;
    int secondX = args.second.first;
    int secondY = args.second.second;
    MultiplyBlockThread(firstX, firstY, secondX, secondY, dimension, first, second, result);
}

std::thread *MatrixMultiply::PushTask(int firstX, int firstY, int secondX, int secondY,
                                      BufferedChannel<std::pair<std::pair<int, int>, std::pair<int, int>>> &channel) {
    std::thread *thr = new std::thread(
            &BufferedChannel<std::pair<std::pair<int, int>, std::pair<int, int>>>::Send,
            ref(channel), std::make_pair(std::make_pair(firstX, firstY), std::make_pair(secondX, secondY)));
    return thr;
}

void MatrixMultiply::MultiplyMatrixChannel(const Vector &first, const Vector &second, Vector &result, int dimension) {
    int length = dimension;
    BufferedChannel<std::pair<std::pair<int, int>, std::pair<int, int>>> channel(length);
    result.zeros(first.size());
    std::vector<std::thread *> threads_push;
    std::vector<std::thread *> threads_pop;
    for (int i = 0; i < std::ceil(first.size() / (double) dimension); i++) {
        for (int j = 0; j < std::ceil(second.size() / (double) dimension); j++) {
            for (int l = 0; l < std::ceil(result.size() / (double) dimension); l++) {
                threads_push.push_back(
                        MatrixMultiply::PushTask(i * dimension, l * dimension, l * dimension, j * dimension, channel));
            }
        }
    }
    for (int i = 0; i < threads_push.size(); i++) {
        std::thread *thr = new std::thread([&channel, &first, &second, &result, dimension]() {
            MultiplyBlockChannel(channel,
                                 dimension,
                                 first,
                                 second,
                                 result);
        });
        threads_pop.push_back(thr);
    }
    for (std::thread *i: threads_push) {
        i->join();
    }
    for (std::thread *i: threads_pop) {
        i->join();
    }
    for (std::thread *i: threads_push) {
        delete i;
    }
    for (std::thread *i: threads_pop) {
        delete i;
    }
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
    std::vector<std::thread> threads;
    for (int i = 0; i < std::ceil(first.size() / (double) dimension); i++) {
        for (int j = 0; j < std::ceil(second.size() / (double) dimension); j++) {
            for (int l = 0; l < std::ceil(result.size() / (double) dimension); l++) {
                std::thread thr(MultiplyBlockThread, i * dimension, l * dimension, l * dimension, j * dimension,
                                dimension,
                                std::ref(first), std::ref(second), std::ref(result));
                threads.push_back(move(thr));
            }
        }
    }
    for (std::thread &i: threads) {
        i.join();
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

void MatrixMultiply::MultiplyAllWithChannel(int matrixSize) {
    Vector first(matrixSize, true);
    Vector second(matrixSize, true);
    Vector result(matrixSize);

    std::vector<std::vector<int>> firstVector;
    std::vector<std::vector<int>> secondVector;
    std::vector<std::vector<int>> resultVector;
    first.copyTo(firstVector);
    second.copyTo(secondVector);
    auto start_threads = std::chrono::system_clock::now();
    MultiplyMatrix(firstVector, secondVector, resultVector);
    auto end_threads = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds_thread = end_threads - start_threads;
    std::cout << "Time: " << elapsed_seconds_thread.count() << ", No threads" << '\n' << '\n';
    auto start_channel = start_threads;
    auto end_channel = end_threads;
    auto elapsed_seconds_channel = elapsed_seconds_thread;
    for (int i = matrixSize; i >= 1; i--) {
        start_threads = std::chrono::system_clock::now();
        MultiplyMatrixThread(first, second, result, i);
        end_threads = std::chrono::system_clock::now();
        elapsed_seconds_thread = end_threads - start_threads;

        start_channel = std::chrono::system_clock::now();
        MultiplyMatrixChannel(first, second, result, i);
        end_channel = std::chrono::system_clock::now();
        elapsed_seconds_channel = end_channel - start_channel;

        std::cout << "Thread Time: " << elapsed_seconds_thread.count()
                  << ", Channel Time: " << elapsed_seconds_channel.count() << ", Number of Blocks: " << i << '\n';
    }
}