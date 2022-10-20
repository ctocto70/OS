#include <iostream>
#include <thread>
#include "BufferedChannel.h"

int main() {
    BufferedChannel<std::string> *channel = new BufferedChannel<std::string>(2);
    std::thread thr1(&BufferedChannel<std::string>::Send, std::ref(channel), "abc");
    std::thread thr2(&BufferedChannel<std::string>::Send, std::ref(channel), "cde");
    std::thread thr3(&BufferedChannel<std::string>::Send, std::ref(channel), "fgh");
    std::thread thr4(&BufferedChannel<std::string>::Recv, std::ref(channel));
    thr1.join();
    thr2.join();
    thr3.join();
    thr4.join();
    std::cout << channel->Recv().first;
    delete channel;
}
