
#include "utility.h"
#include "Profiler.h"
#include <cmath>

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
    while (digitCount < 12)
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

int main()
{
    PROFILE_ME;

    std::vector<std::string> inputData = ReadInputDataFromFileAsVector(".\\resources\\Day3Input.txt");

    for (int i = 0; i < inputData.size(); i++)
    {
        searchGroupSize = inputData[i].size() - maxDepth;
        searchGroupSize++;
        SearchGroupMethod(inputData[i]);
    }

    std::cout << "Total joltage: " << totalJoltage << "\n";

    PROFILE_END;
    profiler::getInstance().print(std::cout, 60);
    system("pause");
}