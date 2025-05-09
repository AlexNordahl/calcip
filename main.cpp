#include <iostream>
#include <string>
#include <vector>
#include <string_view>

std::string intToBinary(int input);
void checkAddress(const std::string input);

int main(int argc, char const *argv[])
{
    checkAddress(argv[1]);
    return 0;
}

std::string intToBinary(int input)
{
    int fitToSize = 8;
    std::string result {};
    
    while (input >= 1)
    {
        result.insert(0, std::to_string(input % 2));
        input /= 2;
    }
    
    int resultSize = result.size();
    for (int i = 0; i < fitToSize - resultSize; i++)
        result.insert(0, "0");
        
    return result;
}

void checkAddress(const std::string input)
{
    const int MASK_MAX = 32;
    const int DOT_MAX = 3;
    const int SLASH_MAX = 1;

    std::string currentOctet {};
    int dotCount = 0;
    int slashCount = 0;
    bool hasMask = false;

    int index = 0;
    for (const char elem : input)
    {
        if (elem == '.')
        {
            int octetValue = std::stoi(currentOctet);
            if (octetValue < 0 or octetValue > 255)
                throw std::invalid_argument("octet out of range");

            currentOctet.clear();

            dotCount++;
            index++;
            continue;
        }

        if (elem == '/')
        {
            if (dotCount != DOT_MAX or SLASH_MAX != 1)
                throw std::invalid_argument("invalid address format");
            
            int maskIndex = index + 1;
            
            if (maskIndex > input.size())
                throw std::invalid_argument("mask was not provided");

            int mask = std::stoi(input.substr(maskIndex));

            if (0 > mask or mask > MASK_MAX)
                throw std::invalid_argument("mask out of range");
            
            hasMask = true;
            slashCount++;
        }

        currentOctet.push_back(elem);
        index++;
    }

    if (!hasMask)
        throw std::invalid_argument("no mask provided");
}