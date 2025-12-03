
#include "utility.h"

long long invalidIdTotal = 0;

bool IsInvalidID(std::string _id)
{
    // If the string is odd length then it can't evenly repeat
    if (_id.size() % 2 > 0)
        return false;

    std::string firstHalf = _id.substr(0, _id.size() / 2);
    std::string secondHalf = _id.substr(_id.size() / 2);

    return firstHalf == secondHalf;
}

void ProcessIDRange(std::string _idRangeString)
{
    std::string lowerBoundStr = "";
    std::string upperBoundStr = "";

    bool foundMiddle = false;

    for (int i = 0; i < _idRangeString.size(); i++)
    {
        if (_idRangeString[i] == '-')
        {
            // Found the hyphen, now start assigning to upper bounds, skip this element
            foundMiddle = true;
            continue;
        }

        if (!foundMiddle)
            lowerBoundStr += _idRangeString[i];
        else
            upperBoundStr += _idRangeString[i];
    }

    // Convert the bounds to numbers
    long long lowerBound = atoll(lowerBoundStr.c_str());
    long long upperBound = atoll(upperBoundStr.c_str());

    // Now go through each number between the bounds (inclusive of bounds)

    for (long long i = lowerBound; i <= upperBound; i++)
    {
        // Covnert i to string and check if it's valid
        std::string idStr = std::to_string(i);
        if (IsInvalidID(idStr))
        {
            //If the id is invalid add to the running total
            invalidIdTotal += i;
        }
    }
}

int main()
{
    std::string inputData = ReadInputDataFromFileAsString(".\\resources\\Day2Input.txt");

    std::string currentIDRange = "";

    for (int i = 0; i < inputData.size(); i++)
    {
        // Jammy delimiter
        if (inputData[i] != ',')
        {
            currentIDRange += inputData[i];
        }
        else
        {
            // Process the current ID Range
            ProcessIDRange(currentIDRange);
            currentIDRange = "";
        }
    }
    ProcessIDRange(currentIDRange);

    std::cout << "Invalid total: " << invalidIdTotal << "\n";

    system("pause");
}