#include "monitorAgent.h"
#include "utils/config.h"
#include "systeminfo.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

int main(int argc, char *argv[])
{
    init_configuration(argc, argv);
    test();
    while (true)
    {
        cout << get_system_cpu_usage() << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }

    return 0;
}