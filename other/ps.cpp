#include <iostream>
#include "./utils.h"

int main() {
    std::cout << "PID" << "\t" << "CMD" << std::endl;
    for (auto pid : get_pids())
        std::cout << pid << "\t" << get_cmd(pid) << "\n";

    return 0;
}