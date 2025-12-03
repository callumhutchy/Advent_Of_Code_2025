
#include <iostream>
#include <stdlib.h>
#include "utility.h"

// Variables to keep track
int wheelValue = 50;
int numberOfZeros = 0;

void CheckWheelForZero()
{
    if (wheelValue == 0)
        numberOfZeros++;
}

void ProcessInstruction(std::string instruction)
{

    char direction = instruction[0];
    int amount = atoi(instruction.c_str() + 1);

    amount = amount % 100;

    switch (direction)
    {
    case 'L':
        if (wheelValue - amount < 0)
        {
            amount -= wheelValue;
            // remove 1 from the remained to account for moving to 99
            amount -= 1;

            wheelValue = 99;
        }
        wheelValue -= amount;
        break;
    case 'R':
        if (wheelValue + amount > 99)
        {
            // whv 95, a 6, remainder 2, remove 1 for 0, so 1
            amount = wheelValue + amount - 99 - 1;
            wheelValue = 0;
        }
        wheelValue += amount;
        break;
    }
}

int main()
{

    // Input data
    std::vector<std::string> instructionInput = ReadInputDataFromFileAsVector(".\\resources\\Day1Input.txt");

    for (int i = 0; i < instructionInput.size(); i++)
    {
        // Safety check incase any input is null
        if (instructionInput[i].size() < 1)
            continue;

        ProcessInstruction(instructionInput[i]);

        CheckWheelForZero();
    }

    std::cout << "Number of times the wheel was on 0: " << numberOfZeros << std::endl;

    system("pause");
}