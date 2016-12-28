#include "monitorAgent.h"
#include "utils/config.h"
#include <iostream>

int main(int argc, char *argv[])
{
    init_configuration(argc, argv);
    test();

    return 0;
}