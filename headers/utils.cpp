#include "utils.hpp"

#define MASK_MAX 32
#define ADDRESS_DOT_MAX 3
#define ADDRESS_SLASH_MAX 1

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

int parseOctet(std::string value)
{
    int octetValue = std::stoi(value);
    if (octetValue < 0 or octetValue > 255)
        throw std::invalid_argument("value out of range");
    return octetValue;
}

std::vector<int> parseAddress(const std::string input)
{
    std::vector<int> result;
    std::string currentOctet {};
    int dotCount = 0;
    int slashCount = 0;
    bool hasMask = false;

    int index = 0;
    for (const char elem : input)
    {
        if (elem == '.')
        {
            int octetValue = parseOctet(currentOctet);
            result.push_back(octetValue);
            currentOctet.clear();

            dotCount++;
            index++;
            continue;
        }

        if (elem == '/')
        {
            int octetValue = parseOctet(currentOctet);
            result.push_back(octetValue);

            if (dotCount != ADDRESS_DOT_MAX or ADDRESS_SLASH_MAX != 1)
                throw std::invalid_argument("invalid address format");
            
            int maskIndex = index + 1;
            
            if (maskIndex > input.size())
                throw std::invalid_argument("mask was not provided");

            int mask = std::stoi(input.substr(maskIndex));

            if (0 > mask or mask > MASK_MAX)
                throw std::invalid_argument("mask out of range");
            
            hasMask = true;
            slashCount++;
            result.push_back(mask);
            break;
        }

        currentOctet.push_back(elem);
        index++;
    }

    if (!hasMask)
        throw std::invalid_argument("no mask provided");

    return result;
}