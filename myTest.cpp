#include <iostream>
#include "osm.h"

int main(int argc, char* argv[])
{
    std::cout << "!~~~ Operation ~~!" << std::endl;
    std::cout << osm_operation_time(50000) << std::endl;
    std::cout << std::endl;

    std::cout << "!~~~ Function ~~!" << std::endl;
    std::cout << osm_function_time(50000) << std::endl;
    std::cout << std::endl;

    std::cout << "!~~~ System Call ~~!" << std::endl;
    std::cout << osm_syscall_time(50000) << std::endl;

    std::cout << "!~~~ Disk ~~!" << std::endl;
    std::cout << osm_disk_time(50000) << std::endl;
}

