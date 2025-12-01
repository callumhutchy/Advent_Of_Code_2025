#include <vector>
#include <string>
#include <iostream>
#include <fstream>

std::vector<std::string> ReadInputDataFromFile(std::string _fileName)
{
    std::vector<std::string> returnBuffer;
    std::ifstream file(_fileName);
    std::string line;
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            returnBuffer.push_back(line);
        }
        file.close();
    }
    return returnBuffer;
}