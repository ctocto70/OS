#include <iostream>
#include <sstream>
#include <cmath>

int main()
{
    std::string str;
    std::getline(std::cin, str);
    std::stringstream ss(str);
    int num;
    while (ss >> num){
        std::cout << pow(num, 3)  << " ";
    }
    std::cout << std::endl;
    return 0;
}
