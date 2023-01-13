
#include <iostream>
#include <sstream>

int main()
{
    int sum = 0;
    std::string str;
    std::getline(std::cin, str);
    std::stringstream ss(str);
    int num;
    while (ss >> num) {
        sum += num;
    }
    std::cout << sum << std::endl;
    return 0;
}
