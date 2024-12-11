#include <math.h>

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

struct LineStruct {
    long target;
    std::vector<int> nums;
};

bool dfs(std::vector<int> &nums, int idx, long total, long target,
         std::string ops);

inline int countDigits(int n)
{
    if (n < 10) return 1;
    if (n < 100) return 2;
    if (n < 1000) return 3;
    return 4;
}

int main(int argc, char *argv[])
{
    std::ifstream ifs;
    ifs.open(argv[1]);
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

    std::ofstream ofs;
    ofs.open("output.txt");
    long total = 0;
    for (auto ls : lines) {
        if (dfs(ls.nums, 1, ls.nums[0], ls.target, "")) {
            ofs << "True\n";
            total += ls.target;
        }
        else {
            ofs << "False\n";
        }
    }

    std::cout << "Result: " << total << '\n';
    return 0;
}

bool dfs(std::vector<int> &nums, int idx, long total, long target,
         std::string ops)
{
    /*
    std::cout << "idx: " << idx << std::endl;
    std::cout << "total: " << total << std::endl;
    */
    if (total > target || idx > nums.size()) {
        return false;
    }
    if (idx == nums.size() && total == target) {
        std::cout << "target: " << target << "\n";
        std::cout << "ops used: " << ops << "\n";
        return true;
    }
    return dfs(nums, idx + 1, total + nums[idx], target, ops + " +") ||
           dfs(nums, idx + 1, total * nums[idx], target, ops + " *") ||
           dfs(nums, idx + 1,
               total * pow(10, countDigits(nums[idx])) + nums[idx], target,
               ops + " ||");
}
