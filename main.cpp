#include <iostream>
#include "headers/utils.hpp"

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        std::cerr << "No address provided as program argument" << std::endl;
        std::exit(1);
    }
        
    std::vector result = parseAddress(argv[1]);

    for (const auto elem : result)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    return 0;
}