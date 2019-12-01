#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <experimental/filesystem>
#include <pwd.h>
#include "./utils.h"


namespace fs = std::experimental::filesystem;

bool is_number(const std::string &str) {
    return std::all_of(str.begin(), str.end(), ::isdigit);
}

std::string get_cmd(const int pid) {
    std::ifstream src("/proc/" + std::to_string(pid) + "/cmdline");
    std::stringstream command;
    command << src.rdbuf();
    return command.str();
}

std::vector<int> get_pids() {
    std::vector<int> pids;
    for (const auto &entry : fs::directory_iterator("/proc/")) {
        auto filename = entry.path().filename();
        if (is_number(filename))
            pids.push_back(std::stoi(filename.u8string()));
    }
    return pids;
}

int get_uid(const int pid) {
    std::fstream file;
    file.open("/proc/" + std::to_string(pid) + "/status");

    std::string uid_line;
    while (uid_line.find("Uid:") != 0 && !file.eof())
        getline(file, uid_line);

    int uid;
    sscanf(uid_line.c_str(), "Uid: %*s %d", &uid);
    return uid;
}

std::string get_user(const int pid) {
    return getpwuid(get_uid(pid))->pw_name;
}