#include "utility.h"
#include "Profiler.h"
#include <math.h>
#include <chrono>
#include <thread>
#include <set>

#define VISUALISATION 0
#define TIMING 1

int totalSplits = 0;

void PrintDashes(std::string _input, std::set<int> _positions)
{
    std::string modifiedString = _input;
    std::set<int>::iterator it;
    for (it = _positions.begin(); it != _positions.end(); ++it)
    {
        modifiedString[*it] = '|';
    }
    std::cout << modifiedString << std::endl;
}

int main()
{
#if TIMING
    PROFILE_ME;
#endif
    std::vector<std::string> inputData = ReadInputDataFromFileAsVector(".\\resources\\Day7Input.txt");

    std::set<int> dashPositions;

    for (int i = 0; i < inputData[0].size(); i++)
    {
        if (inputData[0][i] == 'S')
        {
            dashPositions.insert(i);
        }
    }

    std::cout << inputData[0] << std::endl;

    for (int i = 1; i < inputData.size(); i++)
    {
        std::set<int> newPositions;
        std::set<int>::iterator it;
        for (it = dashPositions.begin(); it != dashPositions.end(); ++it)
        {
            int position = *it;
            if (inputData[i][position] == '^')
            {

                // Split
                newPositions.insert(position + 1);
                newPositions.insert(position - 1);

                totalSplits++;
            }
            else
            {
                newPositions.insert(position);
            }
        }
        PrintDashes(inputData[i], newPositions);
        dashPositions = newPositions;
    }

    std::cout << "\n\nTotal splits: " << totalSplits << std::endl;
#if TIMING
    PROFILE_END;
    profiler::getInstance().print(std::cout, 60);
#endif
    system("pause");
}