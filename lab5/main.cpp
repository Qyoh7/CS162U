#include <iostream>
#include <string>
#include "Library.hpp"

using std::cin;

int main()
{
    Library library("lib.dat");
    unsigned short int choice;
    string title, artist, album, file;
    int durationSeconds;

    while (true)
    {
        cout << "welcome to the song thing\n";
        cout << "Please choose an option by entering a number\n";
        cout << "1. Search by song\n";
        cout << "2. Search by artist\n";
        cout << "3. Add song\n";
        cout << "4. Batch add songs from text file\n";
        cout << "5. Remove song\n";
        cout << "6. Batch remove songs from text file\n";
        cout << "7. Save\n";
        cout << "8. Exit\n";

        cin >> choice;
        cin.ignore(); // clear newline
        cout << "\n";

        switch (choice)
        {
            case 1:
                cout << "Enter song title: ";
                getline(cin, title);
                library.searchByTitle(title);
                break;

            case 2:
                cout << "Enter artist name: ";
                getline(cin, artist);
                library.searchByArtist(artist);
                break;

            case 3:
                cout << "Enter title: ";
                getline(cin, title);

                cout << "Enter artist: ";
                getline(cin, artist);

                cout << "Enter album: ";
                getline(cin, album);

                cout << "Enter duration (seconds): ";
                cin >> durationSeconds;
                cin.ignore();

                library.add(title, artist, album, durationSeconds);
                break;

            case 4:
                cout << "Enter batch file name: ";
                getline(cin, file);
                library.batchAdd(file);
                break;

            case 5:
                cout << "Enter song title to remove: ";
                getline(cin, title);
                library.remove(title);
                break;

            case 6:
                cout << "Enter batch file name: ";
                getline(cin, file);
                library.batchRemove(file);
                break;

            case 7:
                library.save();
                cout << "Library saved.\n";
                break;

            case 8:
                return 0;

            default:
                cout << "Invalid choice.\n";
        }

        cout << "\n";
    }

    return 0;
}
