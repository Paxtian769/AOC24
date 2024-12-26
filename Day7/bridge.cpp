#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool isNum(char c) {
    return ('0' <= c && c <= '9');
}

int toNum(char c) {
    return c-'0';
}

long long int concatenateNums(long long int i, long long int j) {
    long long int k=j;
    long long int mult=1;
    while (k>0) {
        mult = mult * 10;
        k = k / 10;
    }
    return (i*mult)+j;
}

bool operateNums(long long int expected, long long int running_total, int pos, vector<long long int> &num_list) {
    if (pos < num_list.size()-1) {
        bool match = false;
        match = match || operateNums(expected, running_total*num_list[pos], pos+1, num_list);
        match = match || operateNums(expected, running_total+num_list[pos], pos+1, num_list);
        return match;
    }
    else if (pos == num_list.size()-1) {
        bool match = false;
        match = match || (expected == running_total*num_list[pos]);
        match = match || (expected == running_total+num_list[pos]);
        return match;
    }
    else {
        return false;
    }
}

bool operateNums2(long long int expected, long long int running_total, int pos, vector<long long int> &num_list) {
    if (pos < num_list.size()-1) {
        bool match = false;
        match = match || operateNums2(expected, running_total*num_list[pos], pos+1, num_list);
        match = match || operateNums2(expected, running_total+num_list[pos], pos+1, num_list);
        match = match || operateNums2(expected, concatenateNums(running_total, num_list[pos]), pos+1, num_list);
        return match;
    }
    else if (pos == num_list.size()-1) {
        bool match = false;
        match = match || (expected == running_total*num_list[pos]);
        match = match || (expected == running_total+num_list[pos]);
        match = match || (expected == concatenateNums(running_total, num_list[pos]));
        return match;
    }
    else {
        return false;
    }
}

long long int parseResult(string line, int &pos) {
    long long int total = 0;
    for (pos=0; pos<line.length() && isNum(line[pos]); pos++) {
        total = (total*10) + toNum(line[pos]);
    }

    return total;
}

vector<long long int> parseNumList(string line, int pos) {
    vector<long long int> numList;
    while (pos < line.length()) {
        long long int total=0;
        while (isNum(line[pos])) {
            total = (total*10) + toNum(line[pos]);
            pos++;
        }
        numList.push_back(total);
        pos++;
    }
    return numList;
}

int main() {
    string fname = "input.txt";
    ifstream inputFile;
    inputFile.open(fname);
    string line;

    long long int total = 0;
    long long int total2 = 0;

    while (getline(inputFile, line)) {
        int pos=0;
        long long int result = parseResult(line, pos);
        pos += 2;
        vector<long long int> numList = parseNumList(line, pos);

        if (operateNums(result, numList[0], 1, numList)) {
            total += result;
        }

        if (operateNums2(result, numList[0], 1, numList)) {
            total2 += result;
        }
    }

    cout << "Part 1: Total calibration result = " << total << endl;

    cout << "Part 2: Total calibration result = " << total2 << endl;
    return 0;
}
