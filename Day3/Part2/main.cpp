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

std::string removeIgnoredSections(const std::string& file_content) {
    std::regex ignore_pattern(R"(don't\(\)[\s\S]*?(do\(\)|$))");
    return std::regex_replace(file_content, ignore_pattern, "");
}

int main()
{
    std::ifstream ifs("input.txt");
    if (!ifs.is_open()) {
        std::cerr << "Failed to open file";
        return 1;
    }
    std::string line;
    std::string file_content;
    while (std::getline(ifs, line)) {
        file_content += line;
    }
    file_content = removeIgnoredSections(file_content);
    std::cout << "removed str:\n" << file_content << std::endl;
    std::vector<std::string> matches;
    std::sregex_iterator it(file_content.begin(), file_content.end(), pattern);
    std::sregex_iterator end;
    while (it != end) {
        matches.push_back(it->str());
        ++it;
    }
    std::cout << "Total: " << calculate_total(matches) << '\n';
    ifs.close();
}
