#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char *argv[])
{
    std::ifstream ifs(argv[1]);
    if (!ifs.is_open()) {
        std::cerr << "Failed to open file";
        return 1;
    }

    std::string line;
    int num;
    int safe = 0;
    std::getline(ifs, line);

    std::vector<int> file_lengths;
    std::vector<int> free_lengths;
    file_lengths.reserve(line.size());
    free_lengths.reserve(line.size());

    for (size_t i = 0; i < line.size(); ++i) {
        if (i % 2 == 0) {
            file_lengths.push_back(line[i] - '0');
        }
        else {
            free_lengths.push_back(line[i] - '0');
        }
    }

    uint back_idx = file_lengths.size() - 1;
    uint free_idx = 0;
    long checksum = 0;
    uint cur_idx = file_lengths.front();

    while (back_idx > free_idx) {
        while (file_lengths[back_idx] > 0 && free_lengths[free_idx] > 0) {
            checksum += back_idx * cur_idx;
            ++cur_idx;
            --file_lengths[back_idx];
            --free_lengths[free_idx];
        }
        if (free_lengths[free_idx] == 0) {
            ++free_idx;
            for (int i = 0; i < file_lengths[free_idx]; ++i) {
                checksum += cur_idx * free_idx;
                ++cur_idx;
            }
        }
        if (file_lengths[back_idx] == 0) {
            --back_idx;
        }
    }

    std::cout << "Checksum: " << checksum << std::endl;
}

/*
while(back_idx > cur_idx) {
    while (files[back_idx] > 0 && free[free_idx] > 0) {
        
    }
    if (files[back_idx] == 0) {
        --back_idx;
    }
    if (free[free_idx] == 0) {
        // add to sum from files
        // increment cur_idx
        ++free_idx;
    }
}
*/
