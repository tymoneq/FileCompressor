#include <fstream>
#include <cmath>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{

    if (argc > 2)
    {
        cout << "ERROR\n";
        return 0;
    }

    string fileName = argv[1];

    map<string, pair<int, int>> dictionary;

    // reading data from file and creating dictionary of frequency of occurrence
    ifstream file(fileName);
    string row;

    while (file >> row)
        dictionary[row].first++;

    int j = 0;
    for (auto &el : dictionary)
    {
        el.second.second = j;
        j++;
    }

    file.close();

    // compressing a file

    ofstream legend("legend.txt");
    ofstream compress("compress.txt");
    file.open(fileName);

    while (file >> row)
    {
        if (dictionary[row].first > 1 && row.size() > 1)
            compress << '`' << dictionary[row].second;

        else
            compress << row;

        compress << " ";
    }

    for (const auto &el : dictionary)
        if (el.second.first > 1 && el.first.size() > 1)
            legend << el.second.second << " " << el.first << '\n';

    legend.close();
    compress.close();

    return 0;
}