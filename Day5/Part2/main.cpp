#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

void reorder_swap(std::vector<int> &tokens,
                  std::unordered_map<int, std::unordered_set<int>> &deps)
{
    bool no_swap = false;
    while (!no_swap) {
        bool valid = true;
        for (int i = 0; i < tokens.size(); ++i) {
            for (int j = i + 1; j < tokens.size(); ++j) {
                if (deps.count(tokens[i]) && deps[tokens[i]].count(tokens[j])) {
                    // perform swap
                    int temp = tokens[j];
                    tokens[j] = tokens[i];
                    tokens[i] = temp;
                    valid = false;
                    break;
                }
            }
            if (!valid) {
                break;
            };
        }
        if (valid) no_swap = true;
    }
}

int main()
{
    std::fstream fs;
    fs.open("input.txt");
    if (!fs.is_open()) {
        std::cerr << "Failed to open file";
        return 1;
    }

    // Process page ordering rules
    std::string line;

    /* Store direct upstream dependencies
     * If deps[A] contains B, then B must appear BEFORE A
     * */
    std::unordered_map<int, std::unordered_set<int>> deps;
    std::string delimiter = "|";
    while (std::getline(fs, line)) {
        if (line.empty()) break;
        int first, second;
        size_t x = line.find(delimiter);
        first = std::stoi(line.substr(0, x));
        second = std::stoi(line.substr(x + 1, line.size() - x));
        deps[second].insert(first);
    }

    int valid_total = 0;
    int invalid_total = 0;

    // Process updates
    while (std::getline(fs, line)) {
        // std::cout << "here\n";
        if (line.empty()) break;
        std::stringstream ss(line);
        std::string token;
        std::vector<int> tokens;
        // Parse tokens
        while (std::getline(ss, token, ',')) {
            tokens.push_back(std::stoi(token));
        }

        // Is update valid or not
        bool valid = true;
        for (int i = 0; i < tokens.size(); ++i) {
            for (int j = i + 1; j < tokens.size(); ++j) {
                if (deps.count(tokens[i]) && deps[tokens[i]].count(tokens[j])) {
                    valid = false;
                    break;
                }
            }
            if (!valid) break;
        }
        if (!valid) {
            reorder_swap(tokens, deps);
            invalid_total += tokens[tokens.size() / 2];
        }
        else {
            valid_total += tokens[tokens.size() / 2];
        }
    }

    std::cout << "Valid Total: " << valid_total << std::endl;
    std::cout << "Invalid Total: " << invalid_total << std::endl;
}
