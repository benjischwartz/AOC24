#include <fstream>
#include <iostream>
#include <unordered_map>
#include <cassert>

int main() {
    std::fstream fs;
    fs.open("input.txt");
    if (!fs.is_open()) {
        std::cerr << "Failed to open file";
        return 1;
    }
    std::unordered_map<int, int> freq1;
    std::unordered_map<int, int> freq2;
    int a, b;
    while (fs >> a >> b) {
        ++freq1[a];
        ++freq2[b];
    }

    long similarity = 0;
    for (const auto& [key, val] : freq1) {
        similarity += key * freq2[key];
    }

    std::cout << "Similarity: " << similarity << '\n';
    return 0;
}

