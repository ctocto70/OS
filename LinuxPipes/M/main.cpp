#include <iostream>
#include <string>
#include <sstream>

int main() {
    std::string str;
    std::getline(std::cin, str);
    std::stringstream ss(str);
    int num;
    while (ss >> num) {
        std::cout << 7 * num << " ";
    }
    std::cout << std::endl;
    return 0;
}
