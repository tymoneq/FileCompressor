#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

inline int getNum(const string &word) {
    int num = 0;
    int power = 1;

    for (int j = word.size() - 1; j >= 0; j--) {
        num += (word[j] - '0') * power;
        power *= 10;
    }

    return num;
}

int main(int argc, char *argv[]) {
    ifstream legend("legend.txt");
    ifstream compress("compress.txt");

    ofstream decompress("decompress.txt");

    // reading dictionary
    map<int, string> dictionary;
    string row;

    while (getline(legend, row)) {
        string word = "";

        int num = 0;
        for (int i = 0; i < row.size(); i++) {
            if (row[i] == ' ') {
                num = getNum(word);
                word = "";
            } else
                word += row[i];
        }

        dictionary[num] = word;
    }

    legend.close();

    while (compress >> row) {
        if (row[0] == '`') {
            row[0] = '0';
            int num = getNum(row);

            decompress << dictionary[num];
        } else
            decompress << row;

        decompress << " ";
    }

    compress.close();
    decompress.close();

    return 0;
}