#include "utility.h"
#include "Profiler.h"
#include <math.h>
#include <chrono>
#include <thread>

#define VISUALISATION 0
#define TIMING 1

long long total = 0;

std::vector<int> GetNumbersFromLine(std::string _inputString)
{
    std::vector<int> returnVec;
    std::string temp;
    for (int i = 0; i < _inputString.size(); i++)
    {
        if (_inputString[i] == ' ')
        {
            if (temp != " " && temp != "")
            {
                returnVec.push_back(atoi(temp.c_str()));
            }
            temp = "";
        }
        else
        {
            temp += _inputString[i];
        }
    }
    if (temp != " " && temp != "")
    {
        returnVec.push_back(atoi(temp.c_str()));
    }
    return returnVec;
}

std::vector<char> GetDelimitedCharsFromLine(std::string _inputString)
{
    std::vector<char> returnVec;
    char temp;
    for (int i = 0; i < _inputString.size(); i++)
    {
        if (_inputString[i] == ' ')
        {
            if (temp != ' ')
                returnVec.push_back(temp);
            temp = _inputString[i];
        }
        else
        {
            temp = _inputString[i];
        }
    }
    if (temp != ' ')
        returnVec.push_back(temp);
    return returnVec;
}

int main()
{
#if TIMING
    PROFILE_ME;
#endif
    std::vector<std::string> inputData = ReadInputDataFromFileAsVector(".\\resources\\Day6Input.txt");

    std::vector<std::vector<int>> numberLines;
    for (int i = 0; i < inputData.size() - 1; i++)
    {
        numberLines.push_back(GetNumbersFromLine(inputData[i]));
        std::cout << "Size of NumberLines " << (i + 1) << ": " << numberLines[i].size() << " ";
    }
    std::vector<char> operators = GetDelimitedCharsFromLine(inputData[inputData.size() - 1]);
    std::cout << "Size of operators: " << operators.size() << std::endl;

    for (int i = 0; i < numberLines[0].size(); i++)
    {
        long long tempTotal = 0;

        for (int j = 0; j < numberLines.size(); j++)
        {
            int number = numberLines[j][i];

            if (j == 0)
                tempTotal = number;

            else if (operators[i] == '+')
            {
                tempTotal += number;
            }
            else if (operators[i] == '*')
            {
                tempTotal *= number;
            }
        }

        total += tempTotal;
    }

    std::cout << "\n\nTotal available ingredients: " << total << std::endl;
#if TIMING
    PROFILE_END;
    profiler::getInstance().print(std::cout, 60);
#endif
    system("pause");
}