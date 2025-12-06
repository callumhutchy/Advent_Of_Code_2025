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

    std::vector<std::string> numberLines;
    for (int i = 0; i < inputData.size() - 1; i++)
    {
        numberLines.push_back(inputData[i]);
    }
    int maxDigits = numberLines.size();

    std::vector<std::vector<int>> numbersList;

    std::vector<int> currentNumbers;

    for (int i = 0; i < numberLines[0].size(); i++)
    {
        std::string charsAtIndex;
        for (int j = 0; j < maxDigits; j++)
        {
            charsAtIndex += numberLines[j][i];
        }

        // Check if all chars are spaces then move onto next set of numbers

        if (charsAtIndex == "    ")
        {
            numbersList.push_back(currentNumbers);
            currentNumbers.clear();
            continue;
        }

        // Make the current number
        int number = atoi(charsAtIndex.c_str());
        currentNumbers.push_back(number);

        if (i == numberLines[0].size() - 1)
        {
            numbersList.push_back(currentNumbers);
            currentNumbers.clear();
            continue;
        }
    }

    std::vector<char> operators = GetDelimitedCharsFromLine(inputData[inputData.size() - 1]);
    std::cout << "Size of operators: " << operators.size() << std::endl;

    std::cout << "Size of numbersList " << numbersList.size() << std::endl;

    for (int i = 0; i < numbersList.size(); i++)
    {
        long long tempTotal = 0;

        for (int j = 0; j < numbersList[i].size(); j++)
        {
            int number = numbersList[i][j];

            if (j == 0)
            {
                tempTotal = number;
                std::cout << number << " ";
            }
            else if (operators[i] == '+')
            {
                tempTotal += number;
                std::cout << "+ " << number;
            }
            else if (operators[i] == '*')
            {
                tempTotal *= number;
                std::cout << "* " << number;
            }
        }
        std::cout << std::endl;

        total += tempTotal;
    }

    std::cout << "\n\nTotal available ingredients: " << total << std::endl;
#if TIMING
    PROFILE_END;
    profiler::getInstance().print(std::cout, 60);
#endif
    system("pause");
}