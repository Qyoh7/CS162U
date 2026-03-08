#include <cstddef>
#include <iostream>
#include <fstream>
#include <string>
using std::cout;
using std::ios;
using std::fstream;
using std::string;


struct Employee
{
    string fName;
    string lName;
    double rate;
    unsigned short int hours;
};

struct EmployeeArr
{
    Employee* emps;
    size_t SIZE;
};

EmployeeArr readFile(string name)
{
    Employee tmp{};
    fstream f(name, ios::in);
    string line;
    size_t SIZE = 0;
    int field = 0;
    int i = 0;

    if (f)
    {
        std::getline(f, line);
        SIZE = std::stoul(line);
        Employee* emps = new Employee[SIZE];
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
        return EmployeeArr{emps, SIZE};
    }
    else cout << "Error opening file " << name << "\n";
    return EmployeeArr{nullptr, 0};
}

void writeFileBinary(string name, EmployeeArr emps)
{
    fstream fout;
    cout << "opening binary file\n";
    fout.open(name, ios::out | ios::binary);
    cout << "opened binary file\n";

    if (fout)
    {
        fout.write(reinterpret_cast<char*>(&emps.SIZE), sizeof(size_t));
        for (size_t i = 0; i < emps.SIZE; i++)
        {
            int len = emps.emps[i].fName.size();
            fout.write(reinterpret_cast<char*>(&len), sizeof(len));
            fout.write(emps.emps[i].fName.c_str(), len);

            len = emps.emps[i].lName.size();
            fout.write(reinterpret_cast<char*>(&len), sizeof(len));
            fout.write(emps.emps[i].lName.c_str(), len);

            fout.write(reinterpret_cast<char*>(&emps.emps[i].rate), sizeof(double));
            fout.write(reinterpret_cast<char*>(&emps.emps[i].hours), sizeof(unsigned short int));
        }
        fout.close();
    }
    else cout << "Error opening file " << name << "\n";
}

int main()
{
    EmployeeArr emps = readFile("emps.txt");
    for (size_t i = 0; i < emps.SIZE; i++)
    {
        cout << emps.emps[i].fName << " " << emps.emps[i].lName << "\n";
        cout << "rate: " << emps.emps[i].rate << "\n";
        cout << "hours: " << emps.emps[i].hours << "\n";
    }
    writeFileBinary("emps.dat", emps);
    delete[] emps.emps;

    return 0;
}
