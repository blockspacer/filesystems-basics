#include <iostream>
#include <vector>
#include <bitset>

std::vector <uint8_t> to_utf8(const std::vector <uint32_t> &x) {
    std::vector <uint8_t> vector;
    for (const auto &item: x) {
        if (item < 1 << 7) { // 128
            vector.push_back(static_cast<uint8_t>(item));
        } else if (item < 1 << 11) { // 2048
            vector.push_back(static_cast<uint8_t>(0b11000000 | item >> 6));
            vector.push_back(static_cast<uint8_t>(0b10000000 | item >> 0));
        } else if (item < 1 << 16) { // 65536
            vector.push_back(static_cast<uint8_t>(0b11100000 | item >> 12));
            vector.push_back(static_cast<uint8_t>(0b10000000 | item >> 6));
            vector.push_back(static_cast<uint8_t>(0b10000000 | item >> 0));
        } else if (item < 1 << 21) { // 2097152
            vector.push_back(static_cast<uint8_t>(0b11110000 | item >> 18));
            vector.push_back(static_cast<uint8_t>(0b10000000 | item >> 12));
            vector.push_back(static_cast<uint8_t>(0b10000000 | item >> 6));
            vector.push_back(static_cast<uint8_t>(0b10000000 | item >> 0));
        } else {
            std::cerr << "Error: cannot convert \"" << item << "\" " <<
                      "[" << __FUNCTION__ << "]" << std::endl;
            return vector;
        }
    }
    return vector;
}


std::vector <uint32_t> from_utf8(const std::vector <uint8_t> &x) {
    std::vector <uint32_t> vector;
    for (auto i = 0; i < x.size(); i++) {
        auto firstByte = x[i];
        if (firstByte < 1 << 7) { // 128
            vector.push_back(firstByte);
        } else {
            auto additionalBytes = 1;
            while (std::bitset<8>(firstByte)[8 - additionalBytes] != 0) additionalBytes++;
            additionalBytes -= 2;

            auto value = (1 << (6 - additionalBytes)) - 1 & firstByte;
            for (auto j = 0; j < additionalBytes; j++, i++) {
                value <<= 6;
                value |= x[i + 1] & 0b111111;
            }
            vector.push_back(static_cast<uint32_t>(value));
        }
    }
    return vector;
}
