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

/*
iterate through nums
when we encounter a bad level, test two possibilities 
E.g. 1 3 2 4 5
We would:
  remove 2, check_monotonic()
  remove 3, check_monotonic()
*/
void print_vec(std::vector<int>& v) {
    for (auto x : v) {
        std:: cout << x << " ";
    }
    std::cout << "\n";
}
bool check_monotonic_dampened(std::vector<int> &nums)
{
    // check monotonic increasing
    for (int i = 0; i < nums.size() - 1; ++i) {
        int diff = nums[i + 1] - nums[i];
        if (diff < 1 || diff > 3) {
            std::vector<int> nums_a = nums;
            std::vector<int> nums_b = nums;
            nums_a.erase(nums_a.begin() + i);
            nums_b.erase(nums_b.begin() + i + 1);
            if (check_monotonic(nums_a) || check_monotonic(nums_b)) {
                return true;
            }
            else {
                break;
            }
        }
    }
    // check monotonic decreasing
    for (int i = 0; i < nums.size() - 1; ++i) {
        int diff = nums[i] - nums[i + 1];
        if (diff < 1 || diff > 3) {
            std::vector<int> nums_a = nums;
            std::vector<int> nums_b = nums;
            nums_a.erase(nums_a.begin() + i);
            nums_b.erase(nums_b.begin() + i + 1);
            if (check_monotonic(nums_a) || check_monotonic(nums_b)) {
                return true;
            }
            else {
                break;
            }
        }
    }
    return false;
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
        if (check_monotonic_dampened(nums)) ++safe;
    }
    std::cout << "Safe: " << safe << std::endl;
}
