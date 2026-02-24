#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <memory>
using std::cout;
using std::ios;
using std::fstream;
using std::string;
using std::vector;

struct employee
{
    string fName;
    string lName;
    double rate;
    unsigned short int hours;
};

vector<employee> readFile(string name)
{
    employee tmp{};
    vector<employee> employees;
    fstream f(name, ios::in);
    string line;
    int i = 0;

    if (f)
    {
        while (std::getline(f, line))
        {
            int pos = line.find("=");
            string var = line.substr(0, pos);
            string val = line.substr(pos + 1);

            if (var == "fname") tmp.fName = val;
            else if (var == "lname") tmp.lName = val;
            else if (var == "rate") tmp.rate = stod(val);
            else if (var == "hours") tmp.hours = stoi(val);
            if (i == 3)
            {
                employees.push_back(tmp);
                i = 0;
            }
            else i++;
        }
        f.close();
    }
    else cout << "Error opening file " << name << "\n";
    return employees;
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

vector<employee> readFileBinary(string name)
{
    fstream fin;
    int SIZE = 0;
    employee tmp{};
    fin.open(name, ios::in | ios::binary);

    if (fin)
    {
        fin.read(reinterpret_cast<char*>(&SIZE), sizeof(int));
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

int main()
{
    vector<employee> emps = readFile("emps.txt");
    writeFileBinary("emps.dat", emps);

    return 0;
}
