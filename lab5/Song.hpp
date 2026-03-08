#include <string>
using std::string;

class Song
{
    public:
        Song(string title, string artist, string album, int durationSeconds)
        {
            this->title = title;
            this->artist = artist;
            this->album = album;
            this->durationSeconds = durationSeconds;
            next = nullptr;
        }
        Song()
        {
            title = "";
            artist = "";
            album = "";
            durationSeconds = 0;
            next = nullptr;
        }
        Song* next;
        string title;
        string artist;
        string album;
        int durationSeconds;
};
