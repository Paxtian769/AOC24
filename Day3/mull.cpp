#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool isNum(char c) {
    return '0' <= c && c <= '9';
}

long toNum(char c) {
    return c-'0';
}

long parse_num(int &pos, string line) {
    long val = 0;
    while (pos < line.length() && isNum(line[pos])) {
        val = (val*10)+toNum(line[pos]);
        pos++;
    }

    return val;
}

long parse_mul(int &pos, string line) {
    long a=0, b=0;

    if (pos < line.length() && line[pos] == 'u') {
        pos++;
        if (pos < line.length() && line[pos] == 'l') {
            pos++;
            if (pos < line.length() && line[pos] == '(') {
                pos++;
                if (pos < line.length() && isNum(line[pos])) {
                    a = parse_num(pos, line);
                    if (pos < line.length() && line[pos] == ',') {
                        pos++;
                        if (pos < line.length() && isNum(line[pos])) {
                            b = parse_num(pos, line);
                            if (pos < line.length() && line[pos] == ')') {
                                return a*b;
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}

bool parse_dont(int &pos, string line) {
    if (pos < line.length() && line[pos] == 'o') {
        pos++;
        if (pos < line.length() && line[pos] == 'n') {
            pos++;
            if (pos < line.length() && line[pos] == '\'') {
                pos++;
                if (pos < line.length() && line[pos] == 't') {
                    pos++;
                    if (pos < line.length() && line[pos] == '(') {
                        pos++;
                        if (pos < line.length() && line[pos] == ')') {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

bool parse_do(int &pos, string line) {
    if (pos < line.length() && line[pos] == 'o') {
        pos++;
        if (pos < line.length() && line[pos] == '(') {
            pos++;
            if (pos < line.length() && line[pos] == ')') {
                return true;
            }
        }
    }
    return false;
}

long parse_line(string line) {
    long sumOfMults=0;

    // Part 1
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == 'm') {
            i++;
            sumOfMults += parse_mul(i, line);
        }
    }

    return sumOfMults;
}

long parse_line_with_toggle(string line, bool &doMults) {
    long sumOfMults=0;

    for (int i = 0; i < line.length(); i++) {
        if (doMults) {
            if (line[i] == 'm') {
                i++;
                sumOfMults += parse_mul(i, line);
            }
            else if (line[i] == 'd') {
                i++;
                doMults = parse_dont(i, line);
            }
        }
        else {
            if (line[i] == 'd') {
                i++;
                doMults = parse_do(i, line);
            }
        }
    }

    return sumOfMults;
}

int main() {
    string fname = "input.txt";
    ifstream inputFile;
    inputFile.open(fname);
    string line;

    long sumOfMults=0;
    long sumOfMultsWithToggle=0;
    bool doMults=true;

    while (getline(inputFile, line)) {
        // Part 1
        sumOfMults += parse_line(line);

        // Part 2
        sumOfMultsWithToggle += parse_line_with_toggle(line, doMults);
    }

    cout << "Part 1: Sum of multiplications = " << sumOfMults << endl;

    cout << "Part 2: Sum of multiplications with toggle " << sumOfMultsWithToggle << endl;
}
