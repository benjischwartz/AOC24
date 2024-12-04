#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

bool check_monotonic(std::vector<int> &nums)
{
    if (nums.front() == nums.back()) return false;
    if (nums.front() < nums.back()) {
        for (size_t i = 0; i < nums.size() - 1; ++i) {
            int diff = (nums[i + 1] - nums[i]);
            if (diff < 1 || diff > 3) return false;
        }
    }
    else {
        for (size_t i = 0; i < nums.size() - 1; ++i) {
            int diff = (nums[i] - nums[i + 1]);
            if (diff < 1 || diff > 3) return false;
        }
    }
    return true;
}

int main()
{
    std::ifstream ifs("input.txt");
    if (!ifs.is_open()) {
        std::cerr << "Failed to open file";
        return 1;
    }

    std::string line;
    std::vector<int> nums;
    int num;
    int safe = 0;
    while (std::getline(ifs, line)) {
        nums.clear();
        std::istringstream iss(line);
        while (iss >> num) {
            nums.push_back(num);
        }
        if (check_monotonic(nums)) ++safe;
    }
    std::cout << "Safe: " << safe << std::endl;
}
