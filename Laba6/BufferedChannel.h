//
// Created by yarov on 20.10.2022.
//

#ifndef BUFFERED_CHANNEL_H_
#define BUFFERED_CHANNEL_H_

#include <iostream>
#include <queue>
#include <condition_variable>
#include <mutex>

template<typename T>
class BufferedChannel {
    std::queue<T> *buffer;
    int size;
    std::condition_variable condition;
    bool IsBlock;
    std::mutex locker;

public:
    explicit BufferedChannel(int size_) {
        size = size_;
        IsBlock = false;
        buffer = new std::queue<T>();
    }

    ~BufferedChannel() {
        delete buffer;
    }

    void close() {
        IsBlock = true;
    }

    void Send(T value) {
        if (IsBlock) {
            throw std::runtime_error("");
        }
        std::unique_lock<std::mutex> lock(locker);
        condition.wait(lock, [this] { return this->buffer->size() < this->size; });
        buffer->push(value);
        condition.notify_one();
    }

    std::pair<T, bool> Recv() {
        if (IsBlock) {
            return std::pair<T, bool>(T(), false);
        }
        std::unique_lock<std::mutex> lock(locker);
        condition.wait(lock, [this] { return !this->buffer->empty(); });
        T result = buffer->front();
        buffer->pop();
        condition.notify_one();
        return std::pair<T, bool>(result, true);
    }
};

#endif // BUFFERED_CHANNEL_H_