#pragma once

#include <iostream>
#include <vector>
#include <mutex>

class Vector {
    mutable std::recursive_mutex _lock;
    std::vector<std::vector<int>> vector;
public:
    int get(int x, int y) const;

    void add(int x, int y, int value);

    Vector(int size, bool IsRandom = false);

    Vector(std::vector<std::vector<int>> vector);


    int size() const;

    void zeros(int size);

    void generate(int size);

    void print() const;

    void copyTo(std::vector<std::vector<int>>& vec);

    void setVector(const std::vector<std::vector<int>> insert);
};