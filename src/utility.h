#include <vector>
#include <string>
#include <iostream>
#include <fstream>

std::vector<std::string> ReadInputDataFromFileAsVector(std::string _fileName)
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

std::string ReadInputDataFromFileAsString(std::string _fileName)
{
    std::ifstream file(_fileName);
    std::string line = "";
    if (file.is_open())
    {
        std::getline(file, line);
        file.close();
    }
    return line;
}
