#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <vector>

enum Direction {
    Up,
    Down,
    Left,
    Right,
};

inline void update_coordinates(std::vector<std::vector<char>> &grid, int &x,
                               int &y, Direction &direction);

void create_output_file(std::vector<std::vector<char>> &grid);

namespace std {

template <>
struct hash<std::tuple<int, int, int>> {
    inline size_t operator()(const std::tuple<int, int, int> &v) const
    {
        std::hash<int> int_hasher;
        return int_hasher(std::get<0>(v)) ^ int_hasher(std::get<1>(v)) ^
               int_hasher(std::get<2>(v));
    }
};

template <>
struct hash<std::pair<int, int>> {
    inline size_t operator()(const std::pair<int, int> &v) const
    {
        std::hash<int> int_hasher;
        return int_hasher(v.first) & int_hasher(v.second);
    }
};

}  // namespace std

int main()
{
    std::ifstream ifs("input.txt");
    if (!ifs.is_open()) {
        std::cerr << "Failed to open file";
        return 1;
    }

    std::string line;
    std::vector<std::vector<char>> grid;

    // If we encounter {x, y, dir} in set, we have a cycle
    std::unordered_set<std::tuple<int, int, int>> pos_dirs;
    std::pair<int, int> start_pos; /* {col = x, row = y} */

    // Parse grid
    char c;
    while (std::getline(ifs, line)) {
        std::vector<char> row;
        std::istringstream iss(line);
        while (iss >> c) {
            if (c == '^') start_pos = {row.size(), grid.size()};
            row.push_back(c);
        }
        grid.push_back(std::move(row));
    }

    // Get guard's path
    std::unordered_set<std::pair<int, int>> path;
    int x = start_pos.first;
    int y = start_pos.second;
    Direction direction = Direction::Up;
    while (x >= 0 && x < grid[0].size() && y >= 0 && y < grid.size()) {
        path.insert({x, y});
        update_coordinates(grid, x, y, direction);
    }

    // Place obstacles on guard's path
    int obstacle_counter = 0;
    for (std::pair<int, int> p : path) {
        int i = p.second;
        int j = p.first;
        if (grid[i][j] == '#' || grid[i][j] == '^') continue;
        grid[i][j] = '#';
        int x = start_pos.first;
        int y = start_pos.second;
        Direction direction = Direction::Up;
        pos_dirs.clear();
        while (x >= 0 && x < grid[0].size() && y >= 0 && y < grid.size()) {
            if (pos_dirs.count({x, y, direction})) {
                ++obstacle_counter;
                break;
            };
            pos_dirs.insert({x, y, direction});
            update_coordinates(grid, x, y, direction);
        }
        grid[i][j] = '.';
    }
    grid[start_pos.second][start_pos.first] = '^';

    create_output_file(grid);

    std::cout << "Obstacles: " << obstacle_counter << '\n';
}

inline void update_coordinates(std::vector<std::vector<char>> &grid, int &x,
                               int &y, Direction &direction)
{
    switch (direction) {
        case Direction::Up:
            if (y > 0 && grid[y - 1][x] == '#') {
                direction = Direction::Right;
            }
            else {
                --y;
            }
            break;
        case Direction::Down:
            if (y < grid.size() - 1 && grid[y + 1][x] == '#') {
                direction = Direction::Left;
            }
            else {
                ++y;
            }
            break;
        case Direction::Left:
            if (x > 0 && grid[y][x - 1] == '#') {
                direction = Direction::Up;
            }
            else {
                --x;
            }
            break;
        case Direction::Right:
            if (x < grid[0].size() - 1 && grid[y][x + 1] == '#') {
                direction = Direction::Down;
            }
            else {
                ++x;
            }
            break;
    };
}

void create_output_file(std::vector<std::vector<char>> &grid)
{
    std::ofstream ofs("output.txt");
    for (auto row : grid) {
        for (auto cell : row) {
            ofs << cell;
        }
        ofs << '\n';
    }
}
