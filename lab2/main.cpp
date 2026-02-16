#include <unordered_map>

int findMode(int* arr, int numElements)
{
    if (numElements == 0)
    {
        return -1;
    }
    std::unordered_map<int, int> numbers;

    for (int i = 0; i < numElements; i++)
    {
        numbers[arr[i]]++;
    }

    std::pair<int, int> mostCommon{numbers.begin()->first, numbers.begin()->second};

    for (const auto& pair : numbers)
    {
        if (pair.second > mostCommon.second)
        {
            mostCommon = pair;
        }
    }
    if (mostCommon.second == 1) return -1;
    else return mostCommon.first;
}
