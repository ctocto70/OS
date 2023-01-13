#include <iostream>
#include <sstream>

int main()
{
    int n;
    std::string str;
    std::getline(std::cin, str);
    std::stringstream ss(str);
    while (ss >> n) {
        std::cout << 7 * n << " ";
    }
    std::cout << std::endl;
    return 0;
}