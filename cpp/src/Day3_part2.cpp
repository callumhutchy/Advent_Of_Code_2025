
#include "utility.h"
#include "Profiler.h"
#include <cmath>

long long totalJoltage = 0;

int lineCount = 15;
int maxDepth = 12;
int searchGroupSize = lineCount - maxDepth;

int FindBiggest(std::string _bankSubset, int *biggestIndex)
{
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

    int digitCount = 0;
    long long currentRunningTotal = 0;
    int offset = 0;
    while(digitCount < 12)
    {
        std::string subset = _bank.substr(offset, searchGroupSize);

        int biggestIndex;
        int biggest = FindBiggest(subset, &biggestIndex);
        offset += biggestIndex + 1;
        searchGroupSize -= biggestIndex;

        currentRunningTotal += ((biggest - 48) * pow(10, (maxDepth - (1 + digitCount))));
        digitCount++;
    }

    totalJoltage += currentRunningTotal;
}

void ProcessBank(std::string _bank)
{
    PROFILE_ME;
    // We need to go through the bank and find the biggest pair
    int previousBiggest = 0;

    for (int leftDigitIndex = 0; leftDigitIndex < _bank.size() - 1; leftDigitIndex++)
    {
        for (int rightDigitIndex = leftDigitIndex + 1; rightDigitIndex < _bank.size(); rightDigitIndex++)
        {
            int leftDigit = _bank[leftDigitIndex] - 48;
            int rightDigit = _bank[rightDigitIndex] - 48;
            int combined = (leftDigit * 10) + rightDigit;
            if (combined > previousBiggest)
                previousBiggest = combined;
        }
    }

    totalJoltage += previousBiggest;
}

int main()
{
    PROFILE_ME;

    std::vector<std::string> inputData = ReadInputDataFromFileAsVector(".\\resources\\Day3Input.txt");

    for (int i = 0; i < inputData.size(); i++)
    {
        lineCount = inputData[i].size();
        searchGroupSize = lineCount - maxDepth;
        searchGroupSize++;
        SearchGroupMethod(inputData[i]);
    }

    std::cout << "Total joltage: " << totalJoltage << "\n";

    PROFILE_END;
    profiler::getInstance().print(std::cout, 60);
    system("pause");
}