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
    public:
        Library(string fileName)
        {
            ifstream fin;
            size_t len{};
            char* line;
            fin.open(fileName, std::ios::in | std::ios::binary);

            fin.read(reinterpret_cast<char*>(&len), sizeof(size_t));
            head->title.resize(len);
            fin.read(&head->title[0], len);

            fin.read(reinterpret_cast<char*>(&len), sizeof(size_t));
            head->artist.resize(len);
            fin.read(&head->album[0], len);

            fin.read(reinterpret_cast<char*>(&len), sizeof(size_t));
            head->album.resize(len);
            fin.read(&head->album[0], len);

            fin.read(reinterpret_cast<char*>(&head->durationSeconds), sizeof(int));

            Song* tmp = head;

            while (tmp != NULL)
            {
                fin.read(reinterpret_cast<char*>(&len), sizeof(size_t));
                tmp->title.resize(len);
                fin.read(&tmp->title[0], len);

                fin.read(reinterpret_cast<char*>(&len), sizeof(size_t));
                tmp->artist.resize(len);
                fin.read(&tmp->artist[0], len);

                fin.read(reinterpret_cast<char*>(&len), sizeof(size_t));
                tmp->album.resize(len);
                fin.read(&tmp->album[0], len);

                fin.read(reinterpret_cast<char*>(&tmp->durationSeconds), sizeof(int));

                tmp = tmp->next;
            }
        }
        ~Library()
        {
            delete head;
            delete tail;
        }

        void insertAtBeginning(string title, string artist, string album, int durationSeconds)
        {
            Song* newSong =  new Song(title, artist, album, durationSeconds);
            newSong->next = head;
            head = newSong;
        }

        Song* searchBySong(string query)
        {
            Song* tmp = head;
            while (tmp != NULL)
            {
                if (tmp->title == query)
                {
                    return tmp;
                }
                tmp = tmp->next;
            }
            cout << "Could not find song\n";
            return NULL;
        }

        Song* searchByArtist(string query)
        {
            Song* tmp = head;
            while (tmp != NULL)
            {
                if (tmp->artist == query)
                {
                    return tmp;
                }
                tmp = tmp->next;
            }
            cout << "Could not find song\n";
            return NULL;
        }
        void save(string name)
        {
            ofstream fout;
            fout.open(name, std::ios::out | std::ios::binary);
            if (!fout)
            {
                cout << "Failed to open file\n";
                return;
            }
            Song* tmp = head;

            while (tmp != NULL)
            {
                fout.write(reinterpret_cast<char*>(tmp->title.size()), sizeof(size_t));
                fout.write(reinterpret_cast<char*>(&tmp->title), sizeof(string));

                fout.write(reinterpret_cast<char*>(tmp->artist.size()), sizeof(size_t));
                fout.write(reinterpret_cast<char*>(&tmp->artist), sizeof(string));

                fout.write(reinterpret_cast<char*>(tmp->album.size()), sizeof(size_t));
                fout.write(reinterpret_cast<char*>(&tmp->album), sizeof(string));

                fout.write(reinterpret_cast<char*>(&tmp->durationSeconds), sizeof(int));

                tmp = tmp->next;
            }
            fout.close();
        }

        void load(string fileName)
        {

        }


    private:
        Song* head = NULL;
        Song* tail = NULL;
};
