#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

enum class Direction {
    Up,
    Down,
    Left,
    Right,
    UpLeft,
    UpRight,
    DownLeft,
    DownRight
};

std::pair<int, int> get_next_coord(std::pair<int, int> coord,
                                   Direction direction)
{
    switch (direction) {
        case Direction::Up:
            return {coord.first - 1, coord.second};
        case Direction::Down:
            return {coord.first + 1, coord.second};
        case Direction::Left:
            return {coord.first, coord.second - 1};
        case Direction::Right:
            return {coord.first, coord.second + 1};
        case Direction::UpLeft:
            return {coord.first - 1, coord.second - 1};
        case Direction::UpRight:
            return {coord.first - 1, coord.second + 1};
        case Direction::DownLeft:
            return {coord.first + 1, coord.second - 1};
        case Direction::DownRight:
            return {coord.first + 1, coord.second + 1};
    }
}

int dfs(std::vector<std::vector<char>> &matrix, int i, int j, char last,
        Direction direction)
{
    if (i < 0 || i >= matrix.size() || j < 0 || j >= matrix[0].size()) {
        return false;
    }
    int total = 0;
    switch (last) {
        case 'X': {
            if (matrix[i][j] != 'M') return 0;
            auto next_coord = get_next_coord({i, j}, direction);
            return dfs(matrix, next_coord.first, next_coord.second, 'M',
                       direction);
        }
        case 'M': {
            if (matrix[i][j] != 'A') return false;
            auto next_coord = get_next_coord({i, j}, direction);
            return dfs(matrix, next_coord.first, next_coord.second, 'A',
                       direction);
        }
        case 'A':
            if (matrix[i][j] == 'S') {
                std::cout << "Found XMAS. Direction: "
                          << static_cast<int>(direction) << " end coord: " << i
                          << ", " << j << '\n';
            }
            return matrix[i][j] == 'S';
        default:
            // Starting the search
            total = dfs(matrix, i - 1, j, 'X', Direction::Up) +
                    dfs(matrix, i + 1, j, 'X', Direction::Down) +
                    dfs(matrix, i, j - 1, 'X', Direction::Left) +
                    dfs(matrix, i, j + 1, 'X', Direction::Right) +
                    dfs(matrix, i - 1, j - 1, 'X', Direction::UpLeft) +
                    dfs(matrix, i - 1, j + 1, 'X', Direction::UpRight) +
                    dfs(matrix, i + 1, j - 1, 'X', Direction::DownLeft) +
                    dfs(matrix, i + 1, j + 1, 'X', Direction::DownRight);
            break;
    }
    return total;
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
                count += dfs(matrix, i, j, '*', Direction::Up);
            }
        }
    }

    std::cout << "Count: " << count << '\n';
    return 0;
}
