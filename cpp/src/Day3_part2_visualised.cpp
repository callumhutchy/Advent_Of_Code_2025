

#include "utility.h"
#include "Profiler.h"
#include <cmath>
#include <chrono>
#include <thread>

long long totalJoltage = 0;

int maxDepth = 12;
int searchGroupSize;

int FindBiggest(std::string _bankSubset, int *biggestIndex)
{
    PROFILE_ME;
    int biggest = 0;

    for (int i = 0; i < searchGroupSize; i++)
    {
        if (_bankSubset[i] > biggest)
        {
            biggest = _bankSubset[i];
            *biggestIndex = i;
        }
    }
    return biggest;
}

void SearchGroupMethod(std::string _bank)
{
    PROFILE_ME;
    int digitCount = 0;
    long long currentRunningTotal = 0;
    int offset = 0;

    std::cout << _bank;

    std::vector<int> chosenIndexes;

    while (digitCount < 12)
    {
        std::string subset = _bank.substr(offset, searchGroupSize);

        std::cout << "\r";
        for (int i = 0; i < _bank.size(); i++)
        {
            if (i == offset)
                std::cout << "\033[44m";
            else if (i == offset + searchGroupSize)
                std::cout << "\033[0m";

            if (i < offset)
            {
                bool foundChosen = false;
                for (int j = 0; j < chosenIndexes.size(); j++)
                {
                    if (chosenIndexes[j] == i)
                    {
                        std::cout << "\033[32;1;4m" << _bank[i] << "\033[0m";
                        foundChosen = true;
                    }
                }
                if (!foundChosen)
                    std::cout << "\033[38;5;239m" << _bank[i] << "\033[0m";
            }
            else
            {
                std::cout << _bank[i];
            }
        }

        int biggestIndex;
        int biggest = FindBiggest(subset, &biggestIndex);
        chosenIndexes.push_back(offset + biggestIndex);
        offset += biggestIndex + 1;
        searchGroupSize -= biggestIndex;

        currentRunningTotal += ((biggest - 48) * pow(10, (maxDepth - (1 + digitCount))));
        digitCount++;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    std::cout << "\r\033[0m";
    for (int i = 0; i < _bank.size(); i++)
    {
        bool chosenIndex = false;
        for (int j = 0; j < chosenIndexes.size(); j++)
        {
            if (chosenIndexes[j] == i)
            {
                std::cout << "\033[32;1;4m" << _bank[i] << "\033[0m";
                chosenIndex = true;
            }
        }
        if (!chosenIndex)
            std::cout << "\033[38;5;239m" << _bank[i] << "\033[0m";
    }

    std::cout << "\033[0m\n\nSelected: " << currentRunningTotal << "\n\n\n";

    totalJoltage += currentRunningTotal;
}

int main()
{
    PROFILE_ME;

    std::vector<std::string> inputData = ReadInputDataFromFileAsVector(".\\resources\\Day3Input.txt");

    std::cout << "Legend:\n\033[41m  \033[0m Search Group | \033[32m#\033[0m Selected Digits\n\n";

    for (int i = 0; i < inputData.size(); i++)
    {
        std::cout << "Input:\t" << inputData[i] << "\n\n";
        searchGroupSize = inputData[i].size() - maxDepth;
        searchGroupSize++;
        SearchGroupMethod(inputData[i]);
    }

    std::cout << "Total joltage: " << totalJoltage << "\n";

    PROFILE_END;
    profiler::getInstance().print(std::cout, 60);
    system("pause");
}