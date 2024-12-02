#include <fstream>
#include <iostream>
#include <vector>
#include <cassert>

int main() {
    std::fstream fs;
    fs.open("input.txt");
    if (!fs.is_open()) {
        std::cerr << "Failed to open file";
        return 1;
    }
    std::vector<int> list1;
    std::vector<int> list2;
    int a, b;
    while (fs >> a >> b) {
        std::cout << "a: " << a << std::endl;
        std::cout << "b: " << b << std::endl;
        list1.push_back(a);
        list2.push_back(b);
    }
    assert(list1.size() == list2.size());

    sort(list1.begin(), list1.end());
    sort(list2.begin(), list2.end());
    long distance = 0;
    for (int i = 0; i < list1.size(); ++i) {
        distance += std::abs(list1[i] - list2[i]);
    }
    std::cout << "Distance: " << distance << '\n';
    return 0;
}

