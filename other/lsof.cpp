#include <iostream>
#include "./utils.h"


int main() {
    std::cout << "CMD" << "\t" << "PID" << std::endl;
    for (auto pid : getPids())
        std::cout << getCmd(pid) << "\t" << pid << "\n";

    return 0;
}