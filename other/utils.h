#pragma once

#include <string>
#include <vector>

bool is_number(const std::string &str);

std::string get_cmd(const int pid);

std::vector<int> get_pids();

int get_uid(const int pid);

std::string get_user(const int pid);