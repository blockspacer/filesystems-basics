#include <iostream>
#include <vector>
#include <bitset>

int getBytesNum(int v) {
    return 5 - (v < 1 << 7) - (v < 1 << 11) - (v < 1 << 16) - (v < 1 << 21);
}

std::vector <uint8_t> to_utf8(const std::vector <uint32_t> &x) {
    std::vector <uint8_t> vector;
    for (const auto &item: x) {
        switch (getBytesNum(item)) {
            case 1: // < 128
                vector.push_back(static_cast<uint8_t>(item));
                break;
            case 2: // < 2048
                vector.push_back(static_cast<uint8_t>(0b11000000 | item >> 6));
                vector.push_back(static_cast<uint8_t>(0b10000000 | item >> 0));
                break;
            case 3: // < 65536
                vector.push_back(static_cast<uint8_t>(0b11100000 | item >> 12));
                vector.push_back(static_cast<uint8_t>(0b10000000 | item >> 6));
                vector.push_back(static_cast<uint8_t>(0b10000000 | item >> 0));
                break;
            case 4: // < 2097152
                vector.push_back(static_cast<uint8_t>(0b11110000 | item >> 18));
                vector.push_back(static_cast<uint8_t>(0b10000000 | item >> 12));
                vector.push_back(static_cast<uint8_t>(0b10000000 | item >> 6));
                vector.push_back(static_cast<uint8_t>(0b10000000 | item >> 0));
                break;
            default:
                std::cerr << "Error: cannot convert \"" << item << "\" " <<
                          "[" << __FUNCTION__ << "]" << std::endl;
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
            while (std::bitset<8>(firstByte)[8 - additionalBytes] != 0)
                additionalBytes++;
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
