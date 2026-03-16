#include "Warehouse.hpp"
#include <string>
#include <iostream>
using std::string;
using std::cout;
using std::cin;

int main()
{
    Warehouse warehouse;
    int bin;
    int addRemove;

    while (true)
    {
        for (int i = 0; i < 10; i++)
        {
            cout << i + 1 << ". " << warehouse.bins[i].desc << ": " << warehouse.bins[i].numParts << "\n";
        }
        cout << "11. Exit\n\n";

        cout << "Please select an option by entering a number.\n";
        cin >> bin;
        cout << "\n";
        bin -= 1;

        if (bin == 10)
        {
            cout << "Exiting...\n";
            break;
        }
        else if (bin < 0 || bin > 10)
        {
            cout << "Invalid menu choice\n\n";
            continue;
        }
        else {
            while (true)
            {
                cout << "Selected " << warehouse.bins[bin].desc << " bin\n";
                cout << "1. Add parts\n";
                cout << "2. Remove parts\n";
                cin >> addRemove;
                cout << "\n";
                if (addRemove == 1)
                {
                    cout << "Enter amount to add\n";
                    cin >> addRemove;
                    cout << "\n";
                    warehouse.addParts(bin, addRemove);
                    break;
                }
                else if (addRemove == 2)
                {
                    cout << "Enter amount to remove\n";
                    cin >> addRemove;
                    cout << "\n";
                    warehouse.removeParts(bin, addRemove);
                    break;
                }
                else {
                    cout << "Bad menu choice\n";
                }
            }
        }
    }
}
