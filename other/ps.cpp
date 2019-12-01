#include <iostream>
#include "./utils.h"

int main() {
    std::cout << "PID" << "\t" << "CMD" << std::endl;
    for (auto pid : getPids())
        std::cout << pid << "\t" << getCmd(pid) << "\n";

    return 0;
}