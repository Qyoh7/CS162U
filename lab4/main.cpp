#include <iostream>
#include <utility>
#include <fstream>
#include <vector>
#include <string>
using std::cout;
using std::ios;
using std::fstream;
using std::vector;
using std::string;
using std::pair;


struct employee
{
    string fName;
    string lName;
    double rate;
    unsigned short int hours;
};

pair<employee*, size_t> readFile(string name)
{
    employee tmp{};
    fstream f(name, ios::in);
    string line;
    int SIZE = 0;
    int field = 0;
    int i = 0;

    if (f)
    {
        std::getline(f, line);
        SIZE = std::stoi(line);
        employee* emps = new employee[SIZE];
        while (std::getline(f, line))
        {
            int pos = line.find("=");
            string var = line.substr(0, pos);
            string val = line.substr(pos + 1);

            if (var == "fname") tmp.fName = val;
            else if (var == "lname") tmp.lName = val;
            else if (var == "rate") tmp.rate = stod(val);
            else if (var == "hours") tmp.hours = stoi(val);
            if (field == 3)
            {
                emps[i] = tmp;
                field = 0;
                i++;
            }
            else field++;
        }
        f.close();
        return pair<employee*, size_t>(emps, SIZE);
    }
    else cout << "Error opening file " << name << "\n";
    return pair<employee*, size_t>(nullptr, 0);
}

void writeFileBinary(string name, vector<employee> emps)
{
    fstream fout;
    fout.open(name, ios::out | ios::binary);

    if (fout)
    {
        fout.write(reinterpret_cast<char*>(emps.size()), sizeof(size_t));
        for (employee e : emps)
        {
            int len = e.fName.size();
            fout.write(reinterpret_cast<char*>(&len), sizeof(len));
            fout.write(e.fName.c_str(), len);

            len = e.lName.size();
            fout.write(reinterpret_cast<char*>(&len), sizeof(len));
            fout.write(e.lName.c_str(), len);

            fout.write(reinterpret_cast<char*>(&e.rate), sizeof(double));
            fout.write(reinterpret_cast<char*>(&e.hours), sizeof(unsigned short int));
        }
    }
    else cout << "Error opening file " << name << "\n";
}

pair<employee*, size_t> readFileBinary(string name)
{
    fstream fin;
    int SIZE = 0;
    size_t tmp{};
    fin.open(name, ios::in | ios::binary);

    if (fin)
    {
        fin.read(reinterpret_cast<char*>(&SIZE), sizeof(int));
        employee* emps = new employee[SIZE];
        for (int i = 0; i < SIZE; i++)
        {
            int len = emps[i].fName.size();
            fin.write(reinterpret_cast<char*>(&len), sizeof(len));
            fin.write(emps[i].fName.c_str(), len);

            len = emps[i].lName.size();
            fin.write(reinterpret_cast<char*>(&len), sizeof(len));
            fin.write(emps[i].lName.c_str(), len);

            fin.write(reinterpret_cast<char*>(&emps[i].rate), sizeof(double));
            fin.write(reinterpret_cast<char*>(&emps[i].hours), sizeof(unsigned short int));
        }
        return pair<employee*, size_t>(emps, SIZE);
    }
    else cout << "Error opening file " << name << "\n";
}

int main()
{
    pair<employee*, size_t> emps = readFile("emps.txt");
    for (int i = 0; i < emps.second; i++)
    {
        cout << emps.first[i].fName << " " << emps.first[i].lName << "\n";
        cout << "rate: " << emps.first[i].rate << "\n";
        cout << "hours: " << emps.first[i].hours << "\n";
    }

    return 0;
}
