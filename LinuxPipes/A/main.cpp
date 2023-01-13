#include <iostream>
#include <sstream>
int main()
{
    int N = 1;
    std::string str;
    std::getline(std::cin, str);
    std::stringstream ss(str);
    int num;
    while (ss >> num) {
        std::cout << num + N << " ";
    }
    std::cout << std::endl;
    return 0;
}
