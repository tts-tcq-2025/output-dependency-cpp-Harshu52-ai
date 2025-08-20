#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <cassert>
struct ColorPair {
    int pair_number;
    std::string major;
    std::string minor;
};

std::vector<ColorPair> generate_color_map() {
    std::vector<std::string> major_colors = {"White", "Red", "Black", "Yellow", "Violet"};
    std::vector<std::string> minor_colors = {"Blue", "Orange", "Green", "Brown", "Slate"};
    std::vector<ColorPair> color_map;

    for (size_t i = 0; i < major_colors.size(); ++i) {
        for (size_t j = 0; j < minor_colors.size(); ++j) {
            int pair_number = static_cast<int>(i * minor_colors.size() + j);  // Fixing original bug
            color_map.push_back({pair_number, major_colors[i], minor_colors[j]});
        }
    }
    return color_map;
}

std::string format_color_map_entry(const ColorPair& pair) {
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "%d | %-6s | %s", pair.pair_number, pair.major.c_str(), pair.minor.c_str());
    return std::string(buffer);
}

// Print function type
using PrintFunc = std::function<void(const std::string&)>;

int print_color_map(PrintFunc output_func) {
    auto color_map = generate_color_map();
    for (const auto& pair : color_map) {
        output_func(format_color_map_entry(pair));
    }
    return static_cast<int>(color_map.size());
}

// Mock print for test
struct PrintMock {
    std::vector<std::string> calls;

    void operator()(const std::string& line) {
        calls.push_back(line);
    }
};

void test_print_color_map_fail() {
    PrintMock mock_print;

    int count = print_color_map(mock_print);

    // Validate number of lines printed
    assert(count == 25);
    assert(mock_print.calls.size() == 25);

    // Validate first and last entries
    assert(mock_print.calls[0] == "0 | White  | Blue");
    assert(mock_print.calls.back() == "24 | Violet | Slate");

    // You can add more assertions here based on expected content
}

int main() {
    test_print_color_map_fail();
    std::cout << "Test passed!\n";
    return 0;
}
