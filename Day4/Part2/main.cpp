#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

bool check_for_xmas(std::vector<std::vector<char>> &matrix, int i, int j)
{
    return (((matrix[i - 1][j - 1] == 'M' && matrix[i + 1][j + 1] == 'S') ||
             (matrix[i - 1][j - 1] == 'S' && matrix[i + 1][j + 1] == 'M')) &&
            ((matrix[i - 1][j + 1] == 'M' && matrix[i + 1][j - 1] == 'S') ||
             (matrix[i - 1][j + 1] == 'S' && matrix[i + 1][j - 1] == 'M')));
}

int main()
{
    std::fstream fs;
    fs.open("input.txt");
    if (!fs.is_open()) {
        std::cerr << "Failed to open file";
        return 1;
    }
    std::vector<std::vector<char>> matrix;
    std::string line;
    while (std::getline(fs, line)) {
        std::vector<char> chars;
        for (int j = 0; j < line.size(); ++j) {
            chars.push_back(line[j]);
        }
        matrix.push_back(chars);
    }
    int n_rows = matrix.size();
    int n_cols = matrix[0].size();

    int count = 0;
    for (int i = 1; i < n_rows - 1; ++i) {
        for (int j = 1; j < n_cols - 1; ++j) {
            if (matrix[i][j] == 'A') {
                if (check_for_xmas(matrix, i, j)) ++count;
            }
        }
    }

    std::cout << "Count: " << count << '\n';
    return 0;
}
