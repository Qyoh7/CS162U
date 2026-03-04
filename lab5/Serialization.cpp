#include <string>
#include <fstream>
#include <iostream>
#include "Library.hpp"
using std::string;
using std::cout;

void writeFileText(string fileName)
{
    std::ofstream fout;
    fout.open(fileName, std::ios::binary);

    if (fout)
    {
        
    }
    else 
    {
        cout << "Error opening file, maybe learn how to spell?\n";
    }

    
}

Library readFileText(string fileName)
{
    
}

void writeFileBinary(string fileName)
{
    
}

Library readFileBinary(string fileName)
{
    
}
