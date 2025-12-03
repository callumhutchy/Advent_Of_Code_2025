
#include "utility.h"
#include "Profiler.h"

int totalJoltage = 0;

void ProcessBank(std::string _bank)
{
    PROFILE_ME;
    //We need to go through the bank and find the biggest pair
    int previousBiggest = 0;

    for(int leftDigitIndex = 0; leftDigitIndex < _bank.size() - 1; leftDigitIndex++){
        for(int rightDigitIndex = leftDigitIndex + 1; rightDigitIndex < _bank.size(); rightDigitIndex++){
            int leftDigit = _bank[leftDigitIndex] - 48;
            int rightDigit = _bank[rightDigitIndex] - 48;
            int combined = (leftDigit * 10) + rightDigit;
            if(combined > previousBiggest)
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
        ProcessBank(inputData[i]);
    }

    std::cout << "Total joltage: " << totalJoltage << "\n";

    PROFILE_END;
    profiler::getInstance().print(std::cout, 60);
    system("pause");
}