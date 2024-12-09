#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool isNum(char c) {
    return '0' <= c && c <= '9';
}

int toNum(char c) {
    return c-'0';
}

vector<int> parse_line(string line) {
    vector<int> levels;

    int i=0;

    while (i<line.size()) {
        int val=0;
        while (isNum(line[i])) {
            val = val*10+toNum(line[i++]);
        }
        levels.push_back(val);
        while (i<line.size() && !isNum(line[i])) {
            i++;
        }
    }

    return levels;
}

bool isSafeDiff(int val) {
    return (1 <= val && val <= 3);
}

bool isSafeIncreasing(vector<int> report) {
    bool isSafe = true;
    int i=0;
    while (isSafe && i < report.size()-1) {
        int diff = abs(report[i] - report[i+1]);
        isSafe = (report[i] < report[i+1]) && isSafeDiff(diff);
        i++;
    }

    return isSafe;
}

bool isSafeDecreasing(vector<int> report) {
    bool isSafe = true;
    int i=0;
    while (isSafe && i < report.size()-1) {
        int diff = abs(report[i] - report[i+1]);
        isSafe = (report[i] > report[i+1]) && isSafeDiff(diff);
        i++;
    }

    return isSafe;
}

bool isDamperSafe(vector<int> report) {
    if (isSafeIncreasing(report) || isSafeDecreasing(report)) {
        return true;
    }
    else {
        for (int omittedIdx = 0; omittedIdx < report.size(); omittedIdx++) {
            vector<int> newReport;
            for (int i=0; i<report.size(); i++) {
                if (i != omittedIdx) {
                    newReport.push_back(report[i]);
                }
            }

            if (isSafeIncreasing(newReport) || isSafeDecreasing(newReport)) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    string fname = "input.txt";
    ifstream inputFile;
    inputFile.open(fname);
    string line;

    int safeReports=0;
    int damperSafeReports=0;

    while (getline(inputFile, line)) {
        vector<int> report = parse_line(line);
        if (report.size() > 1) {
            if (report[0] < report[1]) {
                if (isSafeIncreasing(report)) {
                    safeReports++;
                }
            }
            else if (report[0] > report[1]) {
                if (isSafeDecreasing(report)) {
                    safeReports++;
                }
            }

            if (isDamperSafe(report)) {
                damperSafeReports++;
            }
        }
    }

    cout << "Part 1: Safe reports = " << safeReports << endl;

    cout << "Part 2: Damper safe reports = " << damperSafeReports << endl;

    return 0;
}
