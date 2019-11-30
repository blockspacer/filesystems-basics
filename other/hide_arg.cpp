#include <sys/prctl.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <sstream>
#include <iostream>

int main(int argc, char **argv) {
    int ret = prctl(PR_SET_MM, PR_SET_MM_ARG_START, ((unsigned long) argv[0]) + strlen(argv[0]), 0, 0);
    if (ret == -1) {
        std::cout << "prctl failed: " << strerror(errno) << "\n";
        return -1;
    }

    std::ostringstream command;
    command << "cat /proc/" << getpid() << "/cmdline";
    std::cout << "$: " << command.str().c_str() << "\n";
    system(command.str().c_str());
    std::cout << "\n";
    return 0;
}