#include "Song.hpp"
#include <cstddef>
#include <iostream>
#include <string>
#include <fstream>
using std::cout;
using std::ofstream;
using std::ifstream;
using std::string;

class Library
{

    private:
        Song* head;
        Song* tail;
        string fileName;
        size_t songCount;

        string readStrBinary(ifstream& fin)
        {
            size_t len;
            string str;

            fin.read(reinterpret_cast<char*>(&len), sizeof(size_t));

            if (len == 0)
                return "";

            str.resize(len);
            fin.read(reinterpret_cast<char*>(str.data()), len);

            return str;
        }

        void writeStrBinary(ofstream& fout, string str)
        {
            size_t len = str.size();
            fout.write(reinterpret_cast<char*>(&len), sizeof(size_t));

            if (len > 0)
                fout.write(str.data(), len);
        }

        void offWithHis(Song* cur)
        {
            while (cur != nullptr)
            {
                Song* next = cur->next;
                delete cur;
                cur = next;
            }
        }

    public:

        Library(string file)
        {
            fileName = file;
            head = nullptr;
            tail = nullptr;
            songCount = 0;

            ifstream fin(fileName, std::ios::binary);

            if (!fin)
            {
                cout << "Failed to load file\n";
                return;
            }

            fin.read(reinterpret_cast<char*>(&songCount), sizeof(size_t));

            for (size_t i = 0; i < songCount; i++)
            {
                Song newSong;

                newSong.title = readStrBinary(fin);
                newSong.artist = readStrBinary(fin);
                newSong.album = readStrBinary(fin);

                fin.read(reinterpret_cast<char*>(&newSong.durationSeconds), sizeof(int));

                add(newSong.title, newSong.artist, newSong.album, newSong.durationSeconds);
            }
        }

        ~Library()
        {
            offWithHis(head);
        }

        void save()
        {
            ofstream fout(fileName, std::ios::binary);

            if (!fout)
            {
                cout << "Failed to save file\n";
                return;
            }

            fout.write(reinterpret_cast<char*>(&songCount), sizeof(size_t));

            Song* tmp = head;

            while (tmp != nullptr)
            {
                writeStrBinary(fout, tmp->title);
                writeStrBinary(fout, tmp->artist);
                writeStrBinary(fout, tmp->album);

                fout.write(reinterpret_cast<char*>(&tmp->durationSeconds), sizeof(int));

                tmp = tmp->next;
            }
        }

        void add(string title, string artist, string album, int durationSeconds)
        {
            Song* cur = head;

            // check duplicates
            while (cur != nullptr)
            {
                if (cur->title == title)
                {
                    cur->artist = artist;
                    cur->album = album;
                    cur->durationSeconds = durationSeconds;
                    return;
                }
                cur = cur->next;
            }

            Song* newSong = new Song(title, artist, album, durationSeconds);

            if (head == nullptr)
            {
                head = newSong;
                tail = newSong;
                songCount++;
                return;
            }

            cur = head;
            Song* prev = nullptr;

            while (cur != nullptr && cur->title < newSong->title)
            {
                prev = cur;
                cur = cur->next;
            }

            if (prev == nullptr)
            {
                newSong->next = head;
                head = newSong;
            }
            else
            {
                newSong->next = cur;
                prev->next = newSong;

                if (cur == nullptr)
                    tail = newSong;
            }

            songCount++;
        }

        void remove(string query)
        {
            Song* cur = head;
            Song* prev = nullptr;

            while (cur != nullptr)
            {
                if (cur->title == query)
                {
                    Song* next = cur->next;

                    if (prev == nullptr)
                        head = next;
                    else
                        prev->next = next;

                    if (next == nullptr)
                        tail = prev;

                    delete cur;
                    songCount--;

                    cout << "Removed song " << query << "\n";
                    return;
                }

                prev = cur;
                cur = cur->next;
            }

            cout << "Could not find song " << query << "\n";
        }

        void displayLibrary()
        {
            Song* tmp = head;

            while (tmp != nullptr)
            {
                cout << "Title: " << tmp->title << "\n";
                cout << "Artist: " << tmp->artist << "\n";
                cout << "Album: " << tmp->album << "\n";
                cout << "Duration: " << tmp->durationSeconds << " seconds\n\n";

                tmp = tmp->next;
            }
        }

        void searchByTitle(string query)
        {
            Song* tmp = head;

            while (tmp != nullptr)
            {
                if (tmp->title == query)
                {
                    cout << "Found song " << query << "\n";
                    return;
                }

                tmp = tmp->next;
            }

            cout << "Could not find song " << query << "\n";
        }

        void searchByArtist(string query)
        {
            Song* tmp = head;
            bool found = false;

            while (tmp != nullptr)
            {
                if (tmp->artist == query)
                {
                    cout << "Found song " << tmp->title << "\n";
                    found = true;
                }

                tmp = tmp->next;
            }

            if (!found)
                cout << "Could not find any songs by " << query << "\n";
        }

        void batchAdd(string fileName)
        {
            ifstream fin(fileName);

            if (!fin)
            {
                cout << "Failed to open batch file\n";
                return;
            }

            string line;
            Song newSong;
            int field = 0;

            while (getline(fin, line))
            {
                if (line.empty())
                    continue;

                int pos = line.find('=');

                string var = line.substr(0, pos);
                string val = line.substr(pos + 1);

                if (var == "title")
                    newSong.title = val;
                else if (var == "artist")
                    newSong.artist = val;
                else if (var == "album")
                    newSong.album = val;
                else if (var == "durationSeconds")
                    newSong.durationSeconds = stoi(val);

                field++;

                if (field == 4)
                {
                    add(newSong.title, newSong.artist, newSong.album, newSong.durationSeconds);
                    field = 0;
                }
            }
        }

        void batchRemove(string fileName)
        {
            ifstream fin(fileName);

            if (!fin)
            {
                cout << "Failed to open batch file\n";
                return;
            }

            string line;

            while (getline(fin, line))
            {
                remove(line);
            }
        }
};
