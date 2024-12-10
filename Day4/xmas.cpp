#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<char> get_row(string line) {
    vector<char> row;
    for (int i=0; i<line.length(); i++) {
        row.push_back(line[i]);
    }

    return row;
}

bool parse_xmas_up(int i, int j, vector<vector<char>> grid) {
    bool xmas_found = false;
    if (grid[i-1][j] == 'M') {
        if (grid[i-2][j] == 'A') {
            if (grid[i-3][j] == 'S') {
                xmas_found=true;
            }
        }
    }

    return xmas_found;
}

bool parse_xmas_up_left(int i, int j, vector<vector<char>> grid) {
    bool xmas_found = false;
    if (grid[i-1][j-1] == 'M') {
        if (grid[i-2][j-2] == 'A') {
            if (grid[i-3][j-3] == 'S') {
                xmas_found=true;
            }
        }
    }

    return xmas_found;
}

bool parse_xmas_up_right(int i, int j, vector<vector<char>> grid) {
    bool xmas_found = false;
    if (grid[i-1][j+1] == 'M') {
        if (grid[i-2][j+2] == 'A') {
            if (grid[i-3][j+3] == 'S') {
                xmas_found=true;
            }
        }
    }

    return xmas_found;
}

bool parse_xmas_left(int i, int j, vector<vector<char>> grid) {
    bool xmas_found = false;
    if (grid[i][j-1] == 'M') {
        if (grid[i][j-2] == 'A') {
            if (grid[i][j-3] == 'S') {
                xmas_found=true;
            }
        }
    }

    return xmas_found;
}

bool parse_xmas_down_left(int i, int j, vector<vector<char>> grid) {
    bool xmas_found = false;
    if (grid[i+1][j-1] == 'M') {
        if (grid[i+2][j-2] == 'A') {
            if (grid[i+3][j-3] == 'S') {
                xmas_found=true;
            }
        }
    }

    return xmas_found;
}

bool parse_xmas_right(int i, int j, vector<vector<char>> grid) {
    bool xmas_found = false;
    if (grid[i][j+1] == 'M') {
        if (grid[i][j+2] == 'A') {
            if (grid[i][j+3] == 'S') {
                xmas_found=true;
            }
        }
    }

    return xmas_found;
}

bool parse_xmas_down_right(int i, int j, vector<vector<char>> grid) {
    bool xmas_found = false;
    if (grid[i+1][j+1] == 'M') {
        if (grid[i+2][j+2] == 'A') {
            if (grid[i+3][j+3] == 'S') {
                xmas_found=true;
            }
        }
    }

    return xmas_found;
}

bool parse_xmas_down(int i, int j, vector<vector<char>> grid) {
    bool xmas_found = false;
    if (grid[i+1][j] == 'M') {
        if (grid[i+2][j] == 'A') {
            if (grid[i+3][j] == 'S') {
                xmas_found=true;
            }
        }
    }

    return xmas_found;
}

bool parse_cross_mas_up(int i, int j, vector<vector<char>> grid) {
    bool cross_mas_found = false;
    if (grid[i][j+2] == 'M') {
        if (grid[i-1][j+1] == 'A') {
            if (grid[i-2][j] == 'S') {
                if (grid[i-2][j+2] == 'S') {
                    cross_mas_found = true;
                }
            }
        }
    }
    return cross_mas_found;
}

bool parse_cross_mas_down(int i, int j, vector<vector<char>> grid) {
    bool cross_mas_found = false;
    if (grid[i][j+2] == 'M') {
        if (grid[i+1][j+1] == 'A') {
            if (grid[i+2][j] == 'S') {
                if (grid[i+2][j+2] == 'S') {
                    cross_mas_found = true;
                }
            }
        }
    }
    return cross_mas_found;
}

bool parse_cross_mas_right(int i, int j, vector<vector<char>> grid) {
    bool cross_mas_found = false;
    if (grid[i][j+2] == 'S') {
        if (grid[i+1][j+1] == 'A') {
            if (grid[i+2][j] == 'M') {
                if (grid[i+2][j+2] == 'S') {
                    cross_mas_found = true;
                }
            }
        }
    }
    return cross_mas_found;
}

bool parse_cross_mas_left(int i, int j, vector<vector<char>> grid) {
    bool cross_mas_found = false;
    if (grid[i][j-2] == 'S') {
        if (grid[i+1][j-1] == 'A') {
            if (grid[i+2][j] == 'M') {
                if (grid[i+2][j-2] == 'S') {
                    cross_mas_found = true;
                }
            }
        }
    }
    return cross_mas_found;
}

int main() {
    string fname = "input.txt";
    ifstream inputFile;
    inputFile.open(fname);
    string line;
    vector<vector<char>> grid;

    int rows=0, columns=0;

    // construct the letter grid
    while (getline(inputFile, line)) {
        vector<char> row = get_row(line);
        grid.push_back(row);
        rows++;
        columns = row.size();
    }

    int xmas_count = 0;

    int x_mas_count = 0;

    for (int i=0; i<rows; i++) {
        for (int j=0; j<columns; j++) {
            // Part 1:
            if (grid[i][j] == 'X') {
                if (i > 2) {
                    xmas_count += parse_xmas_up(i, j, grid);
                    if (j > 2) {
                        xmas_count += parse_xmas_up_left(i, j, grid);
                    }
                    if (j < columns-3) {
                        xmas_count += parse_xmas_up_right(i, j, grid);
                    }
                }
                if (i < rows-3) {
                    xmas_count += parse_xmas_down(i, j, grid);
                    if (j > 2) {
                        xmas_count += parse_xmas_down_left(i, j, grid);
                    }
                    if (j < columns-3) {
                        xmas_count += parse_xmas_down_right(i, j, grid);
                    }
                }
                if (j > 2) {
                    xmas_count += parse_xmas_left(i, j, grid);
                }
                if (j < columns-3) {
                    xmas_count += parse_xmas_right(i, j, grid);
                }
            }

            // Part 2:
            if (grid[i][j] == 'M') {
                if (i > 1 && j < columns-2) {
                    x_mas_count += parse_cross_mas_up(i, j, grid);
                }
                if (i < rows-2) {
                    if (j < columns-2) {
                        x_mas_count += parse_cross_mas_down(i, j, grid);
                        x_mas_count += parse_cross_mas_right(i, j, grid);
                    }
                    if (j > 1) {
                        x_mas_count += parse_cross_mas_left(i, j, grid);
                    }
                }
            }
        }
    }
    cout << "Part 1: Found " << xmas_count << " XMAS's" << endl;
    cout << "Part 2: Found " << x_mas_count << " X-MAS crosses" << endl;
}
