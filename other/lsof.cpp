#include <iostream>
#include "./utils.h"


int main() {
    std::cout << "CMD" << "\t" << "PID" << "\t" << "USER" << std::endl;
    for (auto pid : get_pids())
        std::cout << get_cmd(pid) << "\t" << pid << "\t" << get_user(pid) << "\n";

    return 0;
}