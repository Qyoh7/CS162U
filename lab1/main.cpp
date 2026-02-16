#include <cmath>
#include <iostream>
#include <utility>
using namespace std;
struct rainfallData
{
    string month;
    double rainfall;
};

// probably some of the worst code i've ever written. but hey, it works. 
int main()
{
    const int MONTHS = 12;
    int tmp = 0;

    string months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    rainfallData rainfall[MONTHS];
    
    for (int i = 0; i < MONTHS; i++)
    {
        rainfall[i].month = months[i];
        rainfall[i].rainfall = 0.0;
    }

    for (int i = 0; i < MONTHS; i++)
    {
        cout << "Enter rainfall for " << rainfall[i].month << "\n";
        cin >> tmp;

        if (tmp < 0)
        {
            cout << "Invalid rainfall. Please enter a positive number\n";
            i--;
        }
        else {
            rainfall[i].rainfall = tmp;
        }
    }

    double total = 0;
    for (rainfallData data : rainfall)
    {
        total += data.rainfall;
    }

    cout << "\nTotal Rainfall: " << total << "in\n";
    cout << "Average Rainfall: " << total / MONTHS << "in\n";

    for (int i = 0; i < MONTHS; i++)
    {
        int max = i;
        for (int j = i + 1; j < MONTHS; j++)
        {
            if (rainfall[j].rainfall > rainfall[max].rainfall)
            {
                max = j;
            }
        }
        swap(rainfall[i], rainfall[max]);
    }

    // find max and min
    rainfallData highest = {"", 0};
    rainfallData lowest = {"", MAXFLOAT};
    for (rainfallData data : rainfall)
    {
        if (data.rainfall < lowest.rainfall) lowest = data;
        if (data.rainfall > highest.rainfall) highest = data;
    }

    cout << "Highest rainfall month: " << highest.month << "\n";
    cout << "Lowest rainfall month: " << lowest.month << "\n\n";

    cout << "Leaderboard:\n";

    for (rainfallData cur : rainfall)
    {
        cout << cur.month << ": " << cur.rainfall << "in\n";
    }

}
