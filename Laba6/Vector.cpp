//
// Created by yarov on 13.10.2022.
//

#include "Vector.h"

int Vector::get(int x, int y) const {
    std::lock_guard<std::recursive_mutex> locker(_lock);
    return vector[x][y];
}

void Vector::add(int x, int y, int value) {
    std::lock_guard<std::recursive_mutex> locker(_lock);
    vector[x][y] += value;
}

Vector::Vector(int size, bool IsRandom) {
    srand(time(0));
    if (IsRandom) {
        std::lock_guard<std::recursive_mutex> locker(_lock);
        generate(size);
    } else {
        std::lock_guard<std::recursive_mutex> locker(_lock);
        zeros(size);
    }
}

Vector::Vector(std::vector<std::vector<int>> vector) {
    setVector(vector);
}


int Vector::size() const {
    std::lock_guard<std::recursive_mutex> locker(_lock);
    return vector.size();
}

void Vector::zeros(int size) {
    std::lock_guard<std::recursive_mutex> locker_(_lock);
    vector.clear();
    for (int i = 0; i < size; i++) {
        std::vector<int> vec;
        for (int j = 0; j < size; j++) {
            vec.push_back(0);
        }
        std::lock_guard<std::recursive_mutex> locker(_lock);
        vector.push_back(vec);
    }
}

void Vector::generate(int size) {
    std::lock_guard<std::recursive_mutex> locker_(_lock);
    vector.clear();
    for (int i = 0; i < size; i++) {
        std::vector<int> vec;
        for (int j = 0; j < size; j++) {
            vec.push_back(rand() % 10);
        }
        std::lock_guard<std::recursive_mutex> locker(_lock);
        vector.push_back(vec);
    }
}

void Vector::print() const {
    for (std::vector<int> i: vector) {
        for (int j: i) {
            std::cout << j << " ";
        }
        std::cout << '\n';
    }
}

void Vector::copyTo(std::vector<std::vector<int>> &vec) {
    vec.clear();
    copy(vector.begin(), vector.end(), back_inserter(vec));
}

void Vector::setVector(const std::vector<std::vector<int>> insert) {
    vector.clear();
    copy(insert.begin(), insert.end(), back_inserter(vector));
}