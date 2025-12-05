#include "utility.h"
#include "Profiler.h"
#include <math.h>
#include <chrono>
#include <thread>
#include <set>

#define VISUALISATION 0
#define TIMING 1

long long availableIngredients = 0;

class Range
{
public:
    long long min;
    long long max;

    bool InRange(long long _num)
    {
        return _num >= min && _num <= max;
    }
};

std::vector<Range> ranges;

void AddRangesFromLine(std::string _line)
{
    Range range;

    std::string temp;
    for (int i = 0; i < _line.size(); i++)
    {
        if (_line[i] == '-')
        {
            range.min = atoll(temp.c_str());
            temp = "";
        }
        else
        {
            temp += _line[i];
        }
    }
    range.max = atoll(temp.c_str());

    long long numbersNotFound = 0;
    bool isDirty = false;
    do
    {
        isDirty = false;
        for (int i = 0; i < ranges.size(); i++)
        {
            // If the min is in another range, get the max of that range, that is our new min for this range
            if (range.min >= ranges[i].min && range.max <= ranges[i].max)
            {
                // New range is inside another range, just return
                return;
            }

            if (range.min >= ranges[i].min && range.min <= ranges[i].max)
            {
                // The bottom of our current range is in this other range
                range.min = ranges[i].max + 1;
                isDirty = true;
            }

            if (range.max >= ranges[i].min && range.max <= ranges[i].max)
            {
                range.max = ranges[i].min - 1;
                isDirty = true;
            }
        }
    } while (isDirty);

    ranges.push_back(range);

    availableIngredients += (range.max - range.min) + 1;
}

int main()
{
#if TIMING
    PROFILE_ME;
#endif
    std::vector<std::string> inputData = ReadInputDataFromFileAsVector(".\\resources\\Day5Input.txt");

    for (int i = 0; i < inputData.size(); i++)
    {
        if (inputData[i] == "")
        {
            break;
        }

        AddRangesFromLine(inputData[i]);
    }

    std::cout << "\n\nTotal available ingredients: " << availableIngredients << std::endl;
#if TIMING
    PROFILE_END;
    profiler::getInstance().print(std::cout, 60);
#endif
    system("pause");
}