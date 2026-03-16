#pragma once
#include <iostream>
#include <string>
using std::string;
using std::cout;

class Warehouse
{
    private:
        struct Bin {
            int numParts;
            string desc;
        };
    public:

        Bin bins[10]{};

        Warehouse()
        {
            bins[0].desc = "Valve";
            bins[0].numParts = 10;
            bins[1].desc = "Bearing";
            bins[1].numParts = 5;
            bins[2].desc = "Bushing";
            bins[2].numParts = 15;
            bins[3].desc = "Coupling";
            bins[3].numParts = 21;
            bins[4].desc = "Flange";
            bins[4].numParts = 7;
            bins[5].desc = "Gear";
            bins[5].numParts = 5;
            bins[6].desc = "Gear Housing";
            bins[6].numParts = 5;
            bins[7].desc = "Vacuum Gripper";
            bins[7].numParts = 25;
            bins[8].desc = "Cable";
            bins[8].numParts = 18;
            bins[9].desc = "Rod";
            bins[9].numParts = 12;
        }

        void addParts(int bin, int count)
        {
            if (count + bins[bin].numParts > 30)
            {
                cout << "Too many parts! Maximum capacity 30 per bin\n";
                return;
            }
            else if (count < 0)
            {
                cout << "Cannot add negative parts\n";
                return;
            }
            else if (bin > 9)
            {
                cout << "Invalid bin\n";
                return;
            }

            bins[bin].numParts += count;
        }

        void removeParts(int bin, int count)
        {
            if (bins[bin].numParts - count < 0)
            {
                cout << "Cannot remove more parts than there are\n";
                return;
            }
            else if (count < 0)
            {
                cout << "Cannot remove negative parts\n";
                return;
            }
            else if (bin > 9)
            {
                cout << "Invalid bin\n";
                return;
            }

            bins[bin].numParts -= count;
        }
};
