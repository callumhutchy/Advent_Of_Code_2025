#include "utility.h"
#include "Profiler.h"
#include <map>

void PrintTree(std::vector<std::string> *_inputData)
{
    std::cout << "\033[1;1H";
    for (int i = 0; i < _inputData->size(); i++)
    {
        std::cout << _inputData->at(i) << std::endl;
    }
}

std::map<int, std::map<int, int>> visitedPositions;

long long TraverseTree(int position, int lineNum, std::vector<std::string> *inputData)
{
    PROFILE_ME;
    PrintTree(inputData);
    long long count = 0;
    bool found = false;
    for (int i = lineNum; i < inputData->size(); i++)
    {
        if (inputData->at(i)[position] == '^')
        {
            if (visitedPositions.contains(i) && visitedPositions[i].contains(position))
            {
                return visitedPositions[i][position];
            }
            else
            {
                inputData->at(i)[position - 1] = '|';
                count += TraverseTree(position - 1, i + 1, inputData);

                inputData->at(i)[position + 1] = '|';
                count += TraverseTree(position + 1, i + 1, inputData);

                visitedPositions[i][position] = count;
                return count;
            }
        }
        else
        {
            inputData->at(i)[position] = '|';
        }
    }
    if (!found)
    {
        leafCount[lineNum][position]++;
        return 1;
    }

    std::cout << "Reached here\n";
}

int main()
{
    PROFILE_ME;

    std::vector<std::string> inputData = ReadInputDataFromFileAsVector(".\\resources\\Day7Input.txt");

    int depth;
    int position;

    for (int i = 0; i < inputData[0].size(); i++)
    {
        if (inputData[0][i] == 'S')
        {
            position = i;
            break;
        }
    }
    depth = 1;
    long long count = TraverseTree(position, depth, &inputData);
    PrintTree(&inputData);


    std::cout << count << std::endl;

    //Profiling
    PROFILE_END;
    profiler::getInstance().print(std::cout, 60);
    system("pause");
    return 1;
}