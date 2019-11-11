#include <vector>
#include <iostream>
#include "converter.hpp"

int main() {
    std::vector <uint32_t> vector = {16, 2047, 65535, 65537, 262145};
    std::string testResult = (vector == from_utf8(to_utf8(vector))) ? "OK" : "FAIL";
    std::cout << "Test result: " << testResult << std::endl;
    return 0;
}