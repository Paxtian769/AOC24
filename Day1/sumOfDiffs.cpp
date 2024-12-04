#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;

bool isNum(char c) {
    return '0' <= c && c <= '9';
}

long toNum(char c) {
    return c - '0';
}

void parseNums(string line, long &leftIn, long &rightIn) {
    leftIn = 0;
    rightIn = 0;
    int i=0;
    while (i<line.length() && isNum(line[i])) {
        leftIn = leftIn*10 + toNum(line[i++]);
    }

    while (!isNum(line[i])) {
        i++;
    }

    while (i<line.length() && isNum(line[i])) {
        rightIn = rightIn * 10 + toNum(line[i++]);
    }
}

int main() {
    string fname = "input.txt";
    ifstream inputFile;
    inputFile.open(fname);

    vector<long> left_list;
    vector<long> right_list;

    string line;

    while (getline(inputFile, line)) {
        long leftIn = 0;
        long rightIn = 0;
        parseNums(line, leftIn, rightIn);
        cout << "LeftIn = " << leftIn << ", RightIn = " << rightIn << endl;
        left_list.push_back(leftIn);
        right_list.push_back(rightIn);
    }

    sort(left_list.begin(), left_list.end());
    sort (right_list.begin(), right_list.end());

    long sumOfDiffs = 0;


    for (int i=0; i < left_list.size() && i < right_list.size(); i++) {
        cout << i << ": Left val = " << left_list[i]  << ", Right val = " << right_list[i] << '\n';

        sumOfDiffs += abs(left_list[i] - right_list[i]);
        cout << "current sum = " << sumOfDiffs << endl;
    }

    cout << "Sum of differences = " <<sumOfDiffs << endl;

    return 0;
}
