#include "utility.h"
#include "Profiler.h"
#include <math.h>
#include <chrono>
#include <thread>
#include <set>
#include <map>

#define DEBUGGING 1

int totalSplits = 0;
class Node;

int nodeCount = 0;

std::vector<std::string> permutations;

std::map<int, std::map<int, int>> visitedPositions;

void PrintTreeOld(std::vector<std::string> *_inputData)
{
    std::cout << "\033[1;1H";
    for (int i = 0; i < _inputData->size(); i++)
    {
        std::cout << _inputData->at(i) << std::endl;
    }
}

void PrintTree(std::vector<std::string> *_inputData)
{
    std::cout << "\033[1;1H";
    for (int i = 0; i < _inputData->size(); i++)
    {
        for (int j = 0; j < _inputData->at(i).size(); j++)
        {
            if (visitedPositions.contains(i) && visitedPositions[i].contains(j))
            {
                std::cout << visitedPositions[i][j];
            }
            else
            {
                std::cout << _inputData->at(i)[j];
            }
        }
        std::cout << std::endl;
    }
}

int Split(int depth, int position, std::vector<std::string> *_inputData)
{
#if DEBUGGING
    PROFILE_ME;

    PrintTreeOld(_inputData);
#endif

    int count = 0;

    if (depth == _inputData->size())
    {
        return 1;
    }

    bool found = false;

    for (int i = depth; i < _inputData->size(); i++)
    {
        if ((_inputData->at(i)[position] == '^'))
        {
            found = true;
            if (!visitedPositions[i].contains(position))
            {
#if DEBUGGING
                _inputData->at(i)[position - 1] = '|';
#endif
                count += Split(i + 1, position - 1, _inputData);

#if DEBUGGING
                _inputData->at(i)[position + 1] = '|';
#endif
                count += Split(i + 1, position + 1, _inputData);

                visitedPositions[i].insert(std::pair<int, int>(position, count));
            }
            else
            {
                count = visitedPositions[i][position];
            }

            break;
        }
#if DEBUGGING
        else
        {
            _inputData->at(i)[position] = '|';
        }
#endif
    }
    if (!found)
    {
        count++;
    }

    return count;
}

std::map<int, std::vector<Node *>> nodesAtDepth;

int main()
{
#if DEBUGGING
    PROFILE_ME;
#endif
    std::vector<std::string> inputData = ReadInputDataFromFileAsVector(".\\resources\\Day7Input.txt");

    std::vector<int> dashPositions;

    int depth;
    int position;
    for (int i = 0; i < inputData[0].size(); i++)
    {
        if (inputData[0][i] == 'S')
        {
            position = i;
            depth = 1;
        }
    }

    int totalNodes = Split(depth, position, &inputData);
#if DEBUGGING
    PrintTreeOld(&inputData);
#endif
    std::cout << "\n\nTotal paths: " << totalNodes << std::endl;
#if DEBUGGING
    PROFILE_END;
    profiler::getInstance().print(std::cout, 60);
#endif
    system("pause");
}