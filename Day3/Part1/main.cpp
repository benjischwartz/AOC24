#include <fstream>
#include <iostream>
#include <regex>
#include <string>

std::regex pattern(R"(mul\((-?\d+),(-?\d+)\))");

int calculate_total(const std::vector<std::string>& matches) {
    int total = 0;
    for (const auto& match : matches) {
        std::smatch sm;
        if (std::regex_match(match, sm, pattern)) {
            int x = std::stoi(sm[1].str());
            int y = std::stoi(sm[2].str());
            total += (x * y);
        }
    }
    return total;
}


int main()
{
    std::ifstream ifs("input.txt");
    if (!ifs.is_open()) {
        std::cerr << "Failed to open file";
        return 1;
    }
    std::string line;
    std::vector<std::string> matches;
    while (std::getline(ifs, line)) {
        std::sregex_iterator it(line.begin(), line.end(), pattern);
        std::sregex_iterator end;
        while (it != end) {
            matches.push_back(it->str());
            ++it;
        }
    }
    std::cout << "Total: " << calculate_total(matches) << '\n';
    ifs.close();
}
