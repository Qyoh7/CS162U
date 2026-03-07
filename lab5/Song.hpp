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
        }
        Song* next;
        string title;
        string artist;
        string album;
        int durationSeconds;
};
