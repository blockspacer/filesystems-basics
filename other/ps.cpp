#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

bool isNumber(const std::string &str) {
    return std::all_of(str.begin(), str.end(), ::isdigit);
}

std::string getCmd(const int pid) {
    std::ifstream src("/proc/" + std::to_string(pid) + "/cmdline");
    std::stringstream command;
    command << src.rdbuf();
    return command.str();
}

std::vector<int> getPids() {
    std::vector<int> pids;
    for (const auto &entry : fs::directory_iterator("/proc/")) {
        auto filename = entry.path().filename();
        if (isNumber(filename))
            pids.push_back(std::stoi(filename.u8string()));
    }
    return pids;
}

int main() {
    std::cout << "PID" << "\t" << "CMD" << std::endl;
    for (auto pid : getPids())
        std::cout << pid << "\t" << getCmd(pid) << "\n";

    return 0;
}