#include "utility.h"
#include "Profiler.h"
#include <math.h>
#include <chrono>
#include <thread>

#define VISUALISATION 0
#define TIMING 1

int availableIngredients = 0;

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

Range GetRangeFromLine(std::string _line)
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

    return range;
}

int main()
{
#if TIMING
    PROFILE_ME;
#endif
    std::vector<std::string> inputData = ReadInputDataFromFileAsVector(".\\resources\\Day5Input.txt");

    std::vector<Range> ranges;

    bool beforeGap = true;

    for (int i = 0; i < inputData.size(); i++)
    {
        if (inputData[i] == "")
        {
            beforeGap = false;
            continue;
        }

        if (beforeGap)
        {
            ranges.push_back(GetRangeFromLine(inputData[i]));
        }
        else
        {
            long long id = atoll(inputData[i].c_str());
            
            for(int j =0; j < ranges.size(); j++){
                if(ranges[j].InRange(id)){
                    availableIngredients++;
                    break;
                }
            }
        }
    }

    std::cout << "\n\nTotal available ingredients: " << availableIngredients << std::endl;
#if TIMING
    PROFILE_END;
    profiler::getInstance().print(std::cout, 60);
#endif
    system("pause");
}