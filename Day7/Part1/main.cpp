#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

struct LineStruct {
    long target;
    std::vector<int> nums;
};

bool dfs(std::vector<int> &nums, int idx, long total, long target);

int main()
{
    std::ifstream ifs;
    ifs.open("input.txt");
    if (!ifs.is_open()) {
        std::cerr << "Failed to open file";
        return 1;
    }
    int target;
    std::vector<LineStruct> lines;
    std::string line;
    std::string delimiter = ":";
    while (std::getline(ifs, line)) {
        LineStruct ls;
        size_t x = line.find(delimiter);
        ls.target = std::stol(line.substr(0, x));
        std::istringstream iss(line.substr(x + 1, line.size() - 1));
        int num;
        while (iss >> num) {
            ls.nums.push_back(num);
        }
        lines.push_back(std::move(ls));
    }

    long total = 0;
    for (auto ls : lines) {
        if (dfs(ls.nums, 0, 0, ls.target)) total += ls.target;
    }

    std::cout << "Result: " << total << '\n';
    return 0;
}

bool dfs(std::vector<int> &nums, int idx, long total, long target)
{
    if (total > target || idx > nums.size()) {
        return false;
    }
    if (idx == nums.size() && total == target) {
        return true;
    }
    return dfs(nums, idx + 1, total + nums[idx], target) ||
           dfs(nums, idx + 1, total * nums[idx], target);
}
