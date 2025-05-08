#include <iostream>
#include <string>
#include <list>

std::string decToBinary(int decimal);

int main(int argc, char const *argv[])
{
    try
    {
        int input = std::stoi(argv[1]);
        std::cout << decToBinary(input) << std::endl;
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << "stoi error" << '\n';
    }   
    
    return 0;
}

std::string decToBinary(int decimal)
{
    std::string result {};
    int fitToSize = 8;
    
    while (decimal >= 1)
    {
        result.insert(0, std::to_string(decimal % 2));
        decimal /= 2;
    }
    
    int resultSize = result.size();
    for (int i = 0; i < fitToSize - resultSize; i++)
        result.insert(0, "0");
        
    return result;
}