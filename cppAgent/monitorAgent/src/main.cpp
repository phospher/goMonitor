#include "monitorAgent.h"
#include "utils/config.h"

int main(int argc, char *argv[])
{
    test();
    init_configuration(argc, argv);

    return 0;
}