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
            head = new Song();
            ifstream fin;
            size_t len{};
            char* line;
            size_t songCount;

            fin.open(fileName, std::ios::in | std::ios::binary);
            fin.read(reinterpret_cast<char*>(&songCount), sizeof(size_t));

            fin.read(reinterpret_cast<char*>(&len), sizeof(size_t));
            head->title.resize(len);
            fin.read(&head->title[0], len);

            fin.read(reinterpret_cast<char*>(&len), sizeof(size_t));
            head->artist.resize(len);
            fin.read(&head->artist[0], len);

            fin.read(reinterpret_cast<char*>(&len), sizeof(size_t));
            head->album.resize(len);
            fin.read(&head->album[0], len);

            fin.read(reinterpret_cast<char*>(&head->durationSeconds), sizeof(int));

            Song* tmp = head;
            Song* cur = tmp;

            for (int i = 0; i < songCount - 1; i++)
            {
                Song* newSong = new Song();
                if (i == 0)
                {
                    
                }
                fin.read(reinterpret_cast<char*>(&len), sizeof(size_t));
                newSong->title.resize(len);
                fin.read(&newSong->title[0], len);

                fin.read(reinterpret_cast<char*>(&len), sizeof(size_t));
                newSong->artist.resize(len);
                fin.read(&newSong->artist[0], len);

                fin.read(reinterpret_cast<char*>(&len), sizeof(size_t));
                newSong->album.resize(len);
                fin.read(&newSong->album[0], len);

                fin.read(reinterpret_cast<char*>(&newSong->durationSeconds), sizeof(int));
                
                cur->next = newSong;
                cur = cur->next;
            }
            head = tmp;
        }
        ~Library()
        {
            Song* tmp = head;
            while (tmp != NULL)
            {
                delete tmp;
                tmp = tmp.next;
            }
            head = NULL;
        }

        void add(string title, string artist, string album, int durationSeconds)
        {
            Song* newSong =  new Song(title, artist, album, durationSeconds);
            tail = newSong;
            tail.next = tail;
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

        batchAdd(string fileName)
        {
            ifstream fin;
            fin.open(fileName, std::ios::in);
            char* line;
            int field = 0;
            Song* newSong = new Song("", "", "", 0);
            Song* tmp = head;

            if (!fin)
            {
                cout << "Failed to open file\n";
                return;
            }

            while (getline(fin, line))
            {
                switch (field)
                {
                    case 0:
                        newSong->title = line;
                        break;
                    case 0:
                        newSong->artist = line;
                        break;
                    case 0:
                        newSong->album = line;
                        break;
                    case 3:
                        newSong->durationSeconds = std::stoi(line);
                        break;
                    default:
                        break;
                }
                while (tmp != NULL)
                {
                    if (tmp->next.title.compareTo(newSong->title) > 0)
                    {
                        newSong.next = tmp;
                        tmp = newSong;
                    }
                    tmp = tmp.next;
                }
            }
        }

    private:
        Song* head;
        Song* tail;

        Song* merge(Song* first, Song* second)
        {
            if (first == NULL) return second;
            if (second == NULL) return first;

            if (first.title.compareTo(second) < 0)
            {
                first->next = merge(first->next, second);
                return first;
            }
            else
            {
                second->next = merge(first, second->next);
                return second;
            }
        }

        void sortList()
        {
            
        }
}