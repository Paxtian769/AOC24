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
        left_list.push_back(leftIn);
        right_list.push_back(rightIn);
    }

    sort(left_list.begin(), left_list.end());
    sort (right_list.begin(), right_list.end());


    // Part 1
    long sumOfDiffs = 0;

    for (int i=0; i < left_list.size() && i < right_list.size(); i++) {
        sumOfDiffs += abs(left_list[i] - right_list[i]);
    }

    cout << "Part 1: Sum of differences = " <<sumOfDiffs << endl;


    // Part 2
    long similarityScore = 0;

    for (int i=0; i < left_list.size(); i++) {
        int j=0;
        long simScoreAdd = 0;
        while (j < right_list.size() && right_list[j] < left_list[i]) {
            j++;
        }
        if (j < right_list.size()) {
            while (j < right_list.size() && left_list[i] == right_list[j]) {
                simScoreAdd += left_list[i];
                j++;
            }
        }
        similarityScore += simScoreAdd;
    }

    cout << "Part 2: Similarity Score = " << similarityScore << endl;

    return 0;
}
