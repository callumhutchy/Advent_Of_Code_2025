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

class JunctionBox
{
public:
    int x, y, z;

    std::vector<JunctionBox> connectedJunctionBoxes;

    static double Distance(JunctionBox a, JunctionBox b)
    {
        return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2));
    }

    JunctionBox() {}

    JunctionBox(int _x, int _y, int _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    std::string ToString()
    {
        return "{" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + "}";
    }
};

std::vector<JunctionBox> coords;

std::vector<JunctionBox> GetVectorsFromInput(std::vector<std::string> _inputData)
{
    std::vector<JunctionBox> returnVecs;

    for (int i = 0; i < _inputData.size(); i++)
    {
        std::string temp;
        std::vector<int> numbers;
        for (int j = 0; j < _inputData[i].size(); j++)
        {
            if (_inputData[i][j] == ',')
            {
                numbers.push_back(atoi(temp.c_str()));
                temp = "";
                continue;
            }
            temp += _inputData[i][j];
        }
        numbers.push_back(atoi(temp.c_str()));
        returnVecs.push_back({numbers[0], numbers[1], numbers[2]});
    }

    return returnVecs;
}

class JunctionPairs
{
public:
    JunctionBox a;
    JunctionBox b;

    int circuitId = 0;

    std::string ToString()
    {
        return "{" + a.ToString() + "," + b.ToString() + "}";
    }
};

bool CoordPairsEqual(JunctionPairs _a, JunctionPairs _b)
{
    return (_a.a.x == _b.a.x && _a.a.y == _b.a.y && _a.a.z == _b.a.z &&
            _a.b.x == _b.b.x && _a.b.y == _b.b.y && _a.b.z == _b.b.z);
}

std::map<double, std::vector<JunctionPairs>> junctionBoxDistances;

int main()
{
#if TIMING
    PROFILE_ME;
#endif
    std::vector<std::string> inputData = ReadInputDataFromFileAsVector(".\\resources\\Day8Input.txt");

    long long total = 0;
    coords = GetVectorsFromInput(inputData);
    std::cout << "Processed " << coords.size() << " Coords\n";

    for (int i = 0; i < coords.size(); i++)
    {
        for (int j = 0; j < coords.size(); j++)
        {
            if (i == j)
                continue;
            double distance = JunctionBox::Distance(coords[i], coords[j]);

            bool found = false;
            for (int m = 0; m < junctionBoxDistances[distance].size(); m++)
            {
                if (CoordPairsEqual(junctionBoxDistances[distance][m], {coords[j], coords[i]}))
                {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                JunctionPairs cp = {coords[i], coords[j]};
                junctionBoxDistances[distance].push_back(cp);
            }
        }
    }

    int pairsMade = 0;

    std::vector<std::vector<JunctionBox>> circuits;

    for (int i = 0; i < coords.size(); i++)
    {
        circuits.push_back({coords[i]});
    }

    JunctionPairs lastPair;
    std::map<double, std::vector<JunctionPairs>>::iterator it;
    for (it = junctionBoxDistances.begin(); it != junctionBoxDistances.end(); it++)
    {
        /*
        std::cout << it->first << " [\n";
        for (int i = 0; i < it->second.size(); i++)
        {
            std::cout << "\t " << it->second[i].ToString() << std::endl;
        }


        std::cout << "]\n";
        */
        if (circuits.size() > 1)
            lastPair = it->second[0];

        JunctionBox a = it->second[0].a;
        JunctionBox b = it->second[0].b;

        // Need to find if either are already in a circuit, if they are both in different circuits we need to join them

        bool foundA = false;
        bool foundB = false;
        int circuitIndexA;
        int circuitIndexB;
        for (int i = 0; i < circuits.size(); i++)
        {
            std::vector<JunctionBox>::iterator jbit;
            for (jbit = circuits[i].begin(); jbit != circuits[i].end(); jbit++)
            {
                if (jbit->x == a.x && jbit->y == a.y && jbit->z == a.z)
                {
                    // Found
                    circuitIndexA = i;
                    foundA = true;
                }
                else if (jbit->x == b.x && jbit->y == b.y && jbit->z == b.z)
                {
                    // Found
                    circuitIndexB = i;
                    foundB = true;
                }
            }
        }

        // Found both
        if (foundA && foundB)
        {
            // In different circuits
            if (circuitIndexA != circuitIndexB)
            {
                std::vector<JunctionBox> aCirc = circuits[circuitIndexA];
                std::vector<JunctionBox> bCirc = circuits[circuitIndexB];

                if (circuitIndexA > circuitIndexB)
                {
                    circuits.erase(circuits.begin() + circuitIndexA);
                    circuits.erase(circuits.begin() + circuitIndexB);
                }
                else
                {
                    circuits.erase(circuits.begin() + circuitIndexB);
                    circuits.erase(circuits.begin() + circuitIndexA);
                }

                for (int i = 0; i < bCirc.size(); i++)
                {
                    aCirc.push_back(bCirc[i]);
                }

                circuits.push_back(aCirc);
            }
        }

        /*
                for (int i = 0; i < circuits.size(); i++)
                {
                    std::cout << circuits[i].size() << std::endl;
                }
                    */
        pairsMade++;
        if (pairsMade == 1000)
        {
            std::set<int, std::greater<int>> circuitCounts;
            for (int i = 0; i < circuits.size(); i++)
            {
                circuitCounts.insert(circuits[i].size());
            }

            std::cout << circuits.size() << std::endl;

            std::set<int, std::greater<int>>::iterator ccit = circuitCounts.begin();
            int x = *ccit;
            int y = *++ccit;
            int z = *++ccit;

            total = x * y * z;
        }
        // break;
    }

    std::cout << "Total : " << total << std::endl;

    std::cout << "Last pair: " << lastPair.ToString() << std::endl;

    std::cout << "Distance: " << lastPair.a.x * lastPair.b.x << std::endl;

#if TIMING
    PROFILE_END;
    profiler::getInstance().print(std::cout, 60);
#endif
    system("pause");
}