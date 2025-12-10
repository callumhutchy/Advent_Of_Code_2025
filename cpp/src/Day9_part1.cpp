#include "utility.h"
#include "Profiler.h"
#include <math.h>
#include <vector>
#include <chrono>
#include <thread>
#include <unordered_set>
#include <map>
#include <algorithm>
#include <set>

#define VISUALISATION 0
#define TIMING 1

long long abs_val(long long y)
{
    if (y < 0)
        return (y * -1);
    else
        return (y);
}

int main()
{
#if TIMING
    PROFILE_ME;
#endif
    std::vector<std::string> inputData = ReadInputDataFromFileAsVector(".\\resources\\Day9Input.txt");

    int biggestY = 0;
    int biggestX = 0;

    std::vector<std::pair<int, int>> tiles;
    for (int i = 0; i < inputData.size(); i++)
    {

        long long x;
        long long y;
        std::string temp;
        for (int j = 0; j < inputData[i].size(); j++)
        {
            if (inputData[i][j] == ',')
            {
                x = atoll(temp.c_str());
                if (x > biggestX)
                    biggestX = x;
                temp = "";
            }
            else
                temp += inputData[i][j];
        }
        y = atoll(temp.c_str());
        if (y > biggestY)
            biggestY = y;

        tiles.push_back({x, y});
    }

    std::vector<std::vector<char>> map;

    for (int i = 0; i < biggestX; i++)
    {
        map.push_back({});
        for (int j = 0; j < biggestY ;j++)
        {
            map[i].push_back('.');
        }
    }

    for (int i = 0; i < tiles.size(); i++)
    {
        map[tiles[i].first-1][tiles[i].second-1] = '#';
    }

    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            std::cout << map[i][j];
        }
        std::cout << std::endl;
    }

    long long biggestArea = 0;

    for (int i = 0; i < tiles.size(); i++)
    {
        for (int j = 0; j < tiles.size(); j++)
        {
            if (i == j)
                continue;

            // std::cout << "Comparing\n";
            // std::cout << tiles[i].first << "," << tiles[i].second << std::endl;
            // std::cout << tiles[j].first << "," << tiles[j].second << std::endl;

            long long x = abs_val(tiles[i].first - tiles[j].first) + 1;
            long long y = abs_val(tiles[i].second - tiles[j].second) + 1;

            long long area = x * y;

            // std::cout << "area: " << area << std::endl;

            if (area > biggestArea)
                biggestArea = area;
        }
    }

    std::cout << "Biggest area: " << biggestArea << std::endl;

#if TIMING
    PROFILE_END;
    profiler::getInstance().print(std::cout, 60);
#endif
    system("pause");
}