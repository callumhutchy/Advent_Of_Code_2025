

#include "utility.h"
#include "Profiler.h"
#include <cmath>
#include <chrono>
#include <thread>

#define VISUALISATION 0
#define TIMING 1

long long totalJoltage = 0;

int maxDepth = 12;
int searchGroupSize;

int FindBiggest(std::string _bankSubset, int *biggestIndex)
{
#if TIMING
    PROFILE_ME;
#endif
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
#if TIMING
    PROFILE_ME;
#endif
    int digitCount = 0;
    long long currentRunningTotal = 0;
    int offset = 0;

#if VISUALISATION
    std::cout << _bank;
#endif

    std::vector<int> chosenIndexes;

    while (digitCount < 12)
    {
        std::string subset = _bank.substr(offset, searchGroupSize);

#if VISUALISATION
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
#endif

        int biggestIndex;
        int biggest = FindBiggest(subset, &biggestIndex);
        chosenIndexes.push_back(offset + biggestIndex);
        offset += biggestIndex + 1;
        searchGroupSize -= biggestIndex;

        currentRunningTotal += ((biggest - 48) * pow(10, (maxDepth - (1 + digitCount))));
        digitCount++;

#if VISUALISATION
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
#endif
    }

#if VISUALISATION
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
#endif

    totalJoltage += currentRunningTotal;
}

int main()
{
#if TIMING
    PROFILE_ME;
#endif
#if VISUALISATION
    system("pause");

    std::cout << "Legend:\n\033[44m  \033[0m Search Group | \033[32m#\033[0m Selected Digits\n\n";
#endif

    std::vector<std::string> inputData = ReadInputDataFromFileAsVector(".\\resources\\Day3Input.txt");

    for (int i = 0; i < inputData.size(); i++)
    {
#if VISUALISATION
        std::cout << "Input:\t" << inputData[i] << "\n\n";
#endif
        searchGroupSize = inputData[i].size() - maxDepth;
        searchGroupSize++;
        SearchGroupMethod(inputData[i]);
    }

    std::cout << "Total joltage: " << totalJoltage << "\n";

#if TIMING
    PROFILE_END;
    profiler::getInstance().print(std::cout, 60);
#endif

    system("pause");
}