#pragma once

#include <string>
#include <vector>

bool isNumber(const std::string &str);

std::string getCmd(const int pid);

std::vector<int> getPids();