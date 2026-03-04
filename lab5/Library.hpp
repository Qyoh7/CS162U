#include "Song.hpp"
#include <string>
class Library
{
    public:
        Library()
        {
            
        }
        ~Library() { }
        
    private:
        Song* head = NULL;
        Song* tail = NULL;
};
