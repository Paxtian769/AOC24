#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

enum Direction {NORTH, EAST, SOUTH, WEST};

class PotentialSquare {
public:
    int NWposX;
    int NWposY;
    int NEposX;
    int NEposY;
    int SEposX;
    int SEposY;
    int SWposX;
    int SWposY;
    bool isSquare() {
        if (NWposY == NEposY) {
            if (NWposX == SWposX) {
                if (NEposX == SEposX) {
                    if (SWposY == SEposY) {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    void printCoords() {
        cout << "NW x=" << NWposX << ", y=" << NWposY << endl;
        cout << "NE x=" << NEposX << ", y=" << NEposY << endl;
        cout << "SE x=" << SEposX << ", y=" << SEposY << endl;
        cout << "SW x=" << SWposX << ", y=" << SWposY << endl;
    }
};


int main() {
    string fname = "small_input.txt";
    ifstream inputFile;
    inputFile.open(fname);
    string line;

    Direction direction = NORTH;

    vector<vector<char>> grid;

    int posX = 0, posY = 0;
    int obstCounter=0;

    while (getline(inputFile, line)) {
        vector<char> row;
        for (int i=0; i<line.length(); i++) {
            row.push_back(line[i]);
            if (line[i] == '^') {
                posX = i;
                posY = grid.size();
            }
        }
        grid.push_back(row);
    }

    PotentialSquare potSquare;
    potSquare.NWposX = -1;
    potSquare.NWposY = -1;
    potSquare.NEposX = grid[0].size();
    potSquare.NEposY = -1;
    potSquare.SWposX = posX;
    potSquare.SWposY = posY;
    potSquare.SEposX = grid[0].size();
    potSquare.SWposX = grid.size();

    while (posX >= 0 && posX < grid[0].size() && posY >= 0 && posY < grid.size()) {
        grid[posY][posX] = 'X';
        if (direction == NORTH) {
            if (posY > 0) {
                if (grid[posY-1][posX] != '#') {
                    posY = posY - 1;
                    potSquare.NWposX = posX;
                    potSquare.NWposY = posY;
                    if (potSquare.isSquare()) {
                        potSquare.printCoords();
                        cout << "New obstacle at x = " << posX << ", y = " << posY-1 << endl << endl;
                        obstCounter++;
                    }
                }
                else {
                    direction = EAST;
                }
            }
            else {
                posY = posY - 1;
            }
        }
        else if (direction == EAST) {
            if (posX < grid[0].size()-1) {
                if (grid[posY][posX+1] != '#') {
                    posX = posX + 1;
                    potSquare.NEposX = posX;
                    potSquare.NEposY = posY;
                    if (posX == 6 && posY == 7) {
                        cout << "Not catching obstacle here, why?\n";
                        potSquare.printCoords();
                        cout << endl;
                    }
                    if (potSquare.isSquare()) {
                        potSquare.printCoords();
                        cout << "New obstacle at x = " << posX+1 << ", y = " << posY << endl << endl;
                        obstCounter++;
                    }
                }
                else {
                    direction = SOUTH;
                }
            }
            else {
                posX = posX + 1;
            }
        }
        else if (direction == SOUTH) {
            if (posY < grid.size()-1) {
                if (grid[posY+1][posX] != '#') {
                    posY = posY + 1;
                    potSquare.SEposX = posX;
                    potSquare.SEposY = posY;
                    if (potSquare.isSquare()) {
                        potSquare.printCoords();
                        cout << "New obstacle at x = " << posX << ", y = " << posY+1 << endl << endl;
                        obstCounter++;
                    }
                }
                else {
                    direction = WEST;
                }
            }
            else {
                posY = posY + 1;
            }
        }
        else { // direction == WEST
            if (posX > 0) {
                if (grid[posY][posX-1] != '#') {
                    posX = posX - 1;
                    potSquare.SWposX = posX;
                    potSquare.SWposY = posY;
                    if (potSquare.isSquare()) {
                        potSquare.printCoords();
                        cout << "New obstacle at x = " << posX-1 << ", y = " << posY << endl << endl;
                        obstCounter++;
                    }
                }
                else {
                    direction = NORTH;
                }
            }
            else {
                posX = posX - 1;
            }
        }
    }

    int visitCount = 0;
    for (int i=0; i < grid.size(); i++) {
        for (int j=0; j<grid[0].size(); j++) {
            if (grid[i][j] == 'X') {
                visitCount++;
            }
        }
    }

    cout << "Part 1: Unique locations = " << visitCount << endl;

    cout << "Part 2: Obstacle positions = " << obstCounter << endl;

    return 0;
}
