#include "utility.h"
#include "Profiler.h"
#include <math.h>
#include <chrono>
#include <thread>

int numberOfRollsAccessible = 0;

struct Vector2
{
    int x, y;
};

int main()
{

    PROFILE_ME;

    std::vector<std::string> inputData = ReadInputDataFromFileAsVector(".\\resources\\Day4Input.txt");

    system("pause");
    std::cout << "\033[1;1H";

    for (int i = 0; i < inputData.size(); i++)
    {
        std::cout << inputData[i] << std::endl;
    }

    bool rollRemoved = true;
    while (rollRemoved)
    {
        rollRemoved = false;

        std::vector<Vector2> positionsToRemove;

        for (int y = 0; y < inputData.size(); y++)
        {
            for (int x = 0; x < inputData[y].size(); x++)
            {
                if (inputData[y][x] != '@')
                    continue;

                int numberOfRolls = 0;
                // N = y - 1
                if (y - 1 >= 0)
                {
                    if (inputData[y - 1][x] == '@')
                    {
                        numberOfRolls++;
                    }
                }
                // S = y + 1
                if (y + 1 < inputData.size())
                {
                    if (inputData[y + 1][x] == '@')
                    {
                        numberOfRolls++;
                    }
                }
                // E = x + 1
                if (x + 1 < inputData[y].size())
                {
                    if (inputData[y][x + 1] == '@')
                    {
                        numberOfRolls++;
                    }
                }
                // W = x - 1
                if (x - 1 >= 0)
                {
                    if (inputData[y][x - 1] == '@')
                    {
                        numberOfRolls++;
                    }
                }
                // NE = y - 1 && x + 1
                if (y - 1 >= 0 && x + 1 < inputData[y - 1].size())
                {
                    if (inputData[y - 1][x + 1] == '@')
                    {
                        numberOfRolls++;
                    }
                }
                // SE = y + 1 && x + 1
                if (y + 1 < inputData.size() && x + 1 < inputData[y + 1].size())
                {
                    if (inputData[y + 1][x + 1] == '@')
                    {
                        numberOfRolls++;
                    }
                }
                // SE = y + 1 && x - 1
                if (y + 1 < inputData.size() && x - 1 < inputData[y + 1].size())
                {
                    if (inputData[y + 1][x - 1] == '@')
                    {
                        numberOfRolls++;
                    }
                }
                // NW = y - 1 && x - 1
                if (y - 1 >= 0 && x - 1 >= 0)
                {
                    if (inputData[y - 1][x - 1] == '@')
                    {
                        numberOfRolls++;
                    }
                }

                if (numberOfRolls < 4)
                {
                    numberOfRollsAccessible++;
                    positionsToRemove.push_back({x, y});
                    rollRemoved = true;
                }
            }
        }

        for (int i = 0; i < positionsToRemove.size(); i++)
        {
            inputData[positionsToRemove[i].y][positionsToRemove[i].x] = '.';
        }

        std::cout << "\033[1;1H";

        for (int i = 0; i < inputData.size(); i++)
        {
            std::cout << inputData[i] << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    std::cout << "\n\nTotal accessible rolls: " << numberOfRollsAccessible << std::endl;

    PROFILE_END;
    //profiler::getInstance().print(std::cout, 60);
    system("pause");
}