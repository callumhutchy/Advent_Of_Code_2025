#include "utility.h"
#include "Profiler.h"
#include <map>
#include <set>

void PrintTree(std::vector<std::string> *_inputData)
{
    std::cout << "\033[1;1H";
    for (int i = 0; i < _inputData->size(); i++)
    {
        std::cout << _inputData->at(i) << std::endl;
    }
}

std::map<std::pair<int, int>, long long> nodes;

int main()
{
    PROFILE_ME;

    std::vector<std::string> inputData = ReadInputDataFromFileAsVector(".\\resources\\Day7Input.txt");

    for (int i = 0; i < inputData.size(); i++)
    {
        std::set<std::pair<int, int>> lineCoords;
        for (int j = 0; j < inputData[i].size(); j++)
        {
            if (inputData[i][j] == 'S')
            {
                inputData[i][j] = '|';
                nodes[{i, j}] = 1;
            }
            else if (inputData[i][j] == '.')
            {
                if (i > 0 && inputData[i - 1][j] == '|')
                {
                    inputData[i][j] = '|';
                    long long count = nodes[{i - 1, j}];
                    nodes[{i, j}] += count;

                    lineCoords.insert({i, j});
                }
            }
            else if (inputData[i][j] == '^')
            {
                if (inputData[i - 1][j] == '|')
                {
                    inputData[i][j - 1] = '|';
                    inputData[i][j + 1] = '|';
                    long long  count = nodes[{i - 1, j}];
                    nodes[{i, j - 1}] += count;
                    nodes[{i, j + 1}] += count;
                    lineCoords.insert({i, j - 1});
                    lineCoords.insert({i, j + 1});
                }
            }
            else if (inputData[i][j] == '|')
            {
                if (inputData[i - 1][j] == '|')
                {
                    nodes[{i, j}] += nodes[{i - 1, j}];
                }
            }
        }

        std::cout << inputData[i] << std::endl;
        /*
        std::set<std::pair<int, int>>::iterator it;
        for (it = lineCoords.begin(); it != lineCoords.end(); it++)
        {
            std::cout << nodes[{it->first, it->second}] << " ";
        }
        std::cout << std::endl;
        */
    }

    long long total = 0;
    std::map<std::pair<int, int>, long long>::iterator it;
    for (it = nodes.begin(); it != nodes.end(); it++)
    {
        if (it->first.first == inputData.size() - 1)
        {
            std::cout << it->second << " ";
            total += it->second;
        }
    }
    std::cout << std::endl;

    std::cout << total << std::endl;

    // Profiling
    PROFILE_END;
    profiler::getInstance().print(std::cout, 60);
    system("pause");
    return 1;
}