#pragma once

std::vector <uint8_t> to_utf8(const std::vector <uint32_t> &x);

std::vector <uint32_t> from_utf8(const std::vector <uint8_t> &x);

