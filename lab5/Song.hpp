#include <string>
using std::string;

class Song
{
    public:
        Song(string title, string artist, string album, string durationSeconds)
        {
            m_title = title;
            m_artist = artist;
            m_album = album;
            m_durationSeconds = durationSeconds;
        }

        Song* next;
        string getTitle() const { return m_title; }
        string getArtist() const { return m_artist; }
        string getAlbum() const { return m_album; }
        string getDurationSeconds() const { return m_durationSeconds; }

        void setTitle(const string& title) { m_title = title; } 
        void setArtist(const string& artist) { m_artist = artist; } 
        void setAlbum(const string& album) { m_album = album; } 
        void setDurationSeconds(const string& durationSeconds) { m_durationSeconds = durationSeconds; } 
    private:
        string m_title;
        string m_artist;
        string m_album;
        string m_durationSeconds;
};
