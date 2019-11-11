#include <vector>
#include <iostream>
#include <bitset>
#include "converter.hpp"

int main() {
    std::vector <uint32_t> vector = {16, 1998, 32023, 666666};
    auto convertedVector = to_utf8(vector);

    auto index = 0;
    for (auto elem: vector) {
        std::cout << "[";
        for (auto i = 0; i < getBytesNum(elem); i++, index++)
            std::cout << (i ? " " : "") << std::bitset<8>(convertedVector[index]);
        std::cout << "]: " << elem << std::endl;
    }

    std::string testResult = (vector == from_utf8(convertedVector)) ? "OK" : "FAIL";
    std::cout << "Test result: " << testResult << std::endl;
    return 0;
}