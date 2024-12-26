#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    string fname = "input.txt";
    ifstream inputFile;
    inputFile.open(fname);
    string line;

    while (getline(inputFile, line)) {

    }

    cout << endl;
    return 0;
}
