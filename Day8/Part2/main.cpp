#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using CoordT = std::pair<int, int>;

namespace std {

template <>
struct hash<std::pair<int, int>> {
    inline size_t operator()(const std::pair<int, int> &v) const
    {
        std::hash<int> int_hasher;
        return int_hasher(std::get<0>(v)) ^ int_hasher(std::get<1>(v));
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
    std::unordered_map<char, std::vector<CoordT>> freq_mp;

    char c;
    int i = 0;
    int j = 0;
    size_t width = 0;
    size_t height = 0;
    while (std::getline(ifs, line)) {
        j = 0;
        width = line.size();
        std::istringstream iss(line);
        while (iss >> c) {
            if (c != '.') freq_mp[c].push_back({i, j});
            ++j;
        }
        ++i;
        ++height;
    }

    std::unordered_set<CoordT> antinodes;
    for (const auto &[key, val] : freq_mp) {
        // Generate all pairs
        for (size_t i = 0; i < val.size(); ++i) {
            for (size_t j = i + 1; j < val.size(); ++j) {
                // First direction antinode
                CoordT direction_vector = {val[i].first - val[j].first,
                                           val[i].second - val[j].second};
                int x1 = val[i].first;
                int y1 = val[i].second;
                while (x1 >= 0 && x1 < width && y1 >= 0 && y1 < height) {
                    antinodes.insert({x1, y1});
                    x1 += direction_vector.first;
                    y1 += direction_vector.second;
                }
                // Second direction antinode
                direction_vector = {val[j].first - val[i].first,
                                    val[j].second - val[i].second};
                int x2 = val[j].first;
                int y2 = val[j].second;
                while (x2 >= 0 && x2 < width && y2 >= 0 && y2 < height) {
                    antinodes.insert({x2, y2});
                    x2 += direction_vector.first;
                    y2 += direction_vector.second;
                }
            }
        }
    }
    std::cout << "Antinode locations: " << antinodes.size() << std::endl;
}
