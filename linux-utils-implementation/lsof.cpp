#include <iostream>
#include "./utils.hpp"

int main() {
    std::cout << "CMD" << "\t" << "PID" << "\t" << "USER" << std::endl;
    for (auto pid : get_pids())
        std::cout << get_cmd(pid) << "\t" << pid << "\t" << get_user(pid) << std::endl;

    return 0;
}