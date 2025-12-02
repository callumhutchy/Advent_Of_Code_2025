
#include "utility.h"

long long invalidIdTotal = 0;

bool IsInvalidID(std::string _id)
{
    // Any number of repeating groups so odds allowed
    // Max number of groups is the size of the id

    for (int groupSize = 1; groupSize < _id.size(); groupSize++)
    {
        // Iterate through all the possible group sizes.
        // If the group sizes doesn't cleanly divide then we can skip it.
        if (_id.size() % groupSize > 0)
            continue;

        // Now we need to create the check group and compare to the other groups
        std::vector<std::string> compareGroups;

        for (int i = 0; i < _id.size(); i += groupSize)
        {
            compareGroups.push_back(_id.substr(i, groupSize));
        }

        // Check the compare groups if one of them isn't equal we can continue
        std::string initialComparison;
        bool notEqual = false;
        for (int i = 0; i < compareGroups.size(); i++)
        {
            if (i == 0)
                initialComparison = compareGroups[i];
            else if (initialComparison != compareGroups[i])
            {
                notEqual = true;
            }

            if (notEqual)
                break;
        }

        // Found an invalid ID
        if (!notEqual)
        {
            return true;
        }
    }

    return false;
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
            // If the id is invalid add to the running total
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