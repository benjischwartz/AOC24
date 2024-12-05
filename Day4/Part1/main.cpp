#include <cassert>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

std::string XMAS = "XMAS";

bool func(std::vector<std::vector<char>> &matrix, std::pair<int, int> coords,
          int idx, std::function<std::pair<int, int>(int, int)> update_func)
{
    if (idx == 4) return true;
    if (coords.first < 0 || coords.first >= matrix.size() ||
        coords.second < 0 || coords.second >= matrix[0].size() ||
        matrix[coords.first][coords.second] != XMAS[idx])
        return false;
    return func(matrix, update_func(coords.first, coords.second), idx + 1,
                update_func);
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
    for (int i = 0; i < n_rows; ++i) {
        for (int j = 0; j < n_cols; ++j) {
            if (matrix[i][j] == 'X') {
                count += func(matrix, {i, j}, 0, [](int x, int y) {
                    return std::pair<int, int>({x + 1, y});
                });
                count += func(matrix, {i, j}, 0, [](int x, int y) {
                    return std::pair<int, int>({x - 1, y});
                });
                count += func(matrix, {i, j}, 0, [](int x, int y) {
                    return std::pair<int, int>({x, y + 1});
                });
                count += func(matrix, {i, j}, 0, [](int x, int y) {
                    return std::pair<int, int>({x, y - 1});
                });
                count += func(matrix, {i, j}, 0, [](int x, int y) {
                    return std::pair<int, int>({x + 1, y + 1});
                });
                count += func(matrix, {i, j}, 0, [](int x, int y) {
                    return std::pair<int, int>({x - 1, y + 1});
                });
                count += func(matrix, {i, j}, 0, [](int x, int y) {
                    return std::pair<int, int>({x + 1, y - 1});
                });
                count += func(matrix, {i, j}, 0, [](int x, int y) {
                    return std::pair<int, int>({x - 1, y - 1});
                });
            }
        }
    }

    std::cout << "Count: " << count << '\n';
    return 0;
}
