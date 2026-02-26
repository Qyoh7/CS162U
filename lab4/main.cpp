#include <cstddef>
#include <iostream>
#include <fstream>
#include <string>
using std::cout;
using std::ios;
using std::fstream;
using std::string;


struct employee
{
    string fName;
    string lName;
    double rate;
    unsigned short int hours;
};

struct employeeArr
{
    employee* emps;
    size_t SIZE;
};

employeeArr readFile(string name)
{
    employee tmp{};
    fstream f(name, ios::in);
    string line;
    size_t SIZE = 0;
    int field = 0;
    int i = 0;

    if (f)
    {
        std::getline(f, line);
        SIZE = std::stoul(line);
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
        return employeeArr{emps, SIZE};
    }
    else cout << "Error opening file " << name << "\n";
    return employeeArr{nullptr, 0};
}

employeeArr readFileBinary(string name)
{
    fstream fin;
    size_t SIZE = 0;
    employee tmp{};
    char* line;
    fin.open(name, ios::in | ios::binary);

    if (fin)
    {
        fin.read(reinterpret_cast<char*>(&SIZE), sizeof(size_t));
        employee* emps = new employee[SIZE];
        while (fin.read(line, sizeof(char*)))
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
        return employeeArr{emps, SIZE};
}

void writeFileBinary(string name, employeeArr emps)
{
    fstream fout;
    cout << "opening binary file\n";
    fout.open(name, ios::out | ios::binary);
    cout << "opened binary file\n";

    if (fout)
    {
        cout << "writing records\n";
        fout.write(reinterpret_cast<char*>(&emps.SIZE), sizeof(size_t));
        cout << "wrote number of records\n";
        for (int i = 0; i < emps.SIZE; i++)
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
    }
    else cout << "Error opening file " << name << "\n";
}

int main()
{
    employeeArr emps = readFile("emps.txt");
    for (int i = 0; i < emps.SIZE; i++)
    {
        cout << emps.emps[i].fName << " " << emps.emps[i].lName << "\n";
        cout << "rate: " << emps.emps[i].rate << "\n";
        cout << "hours: " << emps.emps[i].hours << "\n";
    }
    cout << "writing file\n";
    writeFileBinary("emps.dat", emps);

    cout << "reading file from binary\n";
    employeeArr empsFromBin = readFileBinary("emps.dat");

    cout << "results: \n";
    for (size_t i = 0; i < empsFromBin.SIZE; i++)
    {
        cout << empsFromBin.emps[i].fName << " " << empsFromBin.emps[i].lName << "\n";
        cout << "rate: " << empsFromBin.emps[i].rate << "\n";
        cout << "hours: " << empsFromBin.emps[i].hours << "\n";
    }
    

    return 0;
}
