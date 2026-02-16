#include <cctype>
#include <iostream>
#include <string.h>
#include <string>

void capitalize(char* sentence)
{
    char* p = sentence;
    bool isFirstLetter = true;

    while (*p != '\0')
    {
        if (isFirstLetter && isalpha(static_cast<unsigned char>(*p)))
        {
            *p = toupper(static_cast<unsigned char>(*p));
            isFirstLetter = false;
        }
        else if (strchr("!?.", *p))
        {
            isFirstLetter = true;
        }
        p++;
    }
}

void capitalize(std::string& sentence)
{
    bool isFirstLetter = true;

    for (char &c : sentence)
    {
        if (isFirstLetter && isalpha(static_cast<unsigned char>(c)))
        {
            c = toupper(static_cast<unsigned char>(c));
            isFirstLetter = false;
        }
        else if (strchr(".?!", c))
        {
            isFirstLetter = true;
        }
    }
}

int main()
{
    char test[] = "this. is. a. test. cstring. sentence.";
    std::string test2 = "this. is. a. string. class.";
    capitalize(test);
    capitalize(test2);
    std::cout << test2;
    for (char c : test)
    {
        std::cout << c;
    }
}
