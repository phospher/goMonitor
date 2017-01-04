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
    cout << get_syetem_cpu_usage() << endl;
    while (true)
    {
        this_thread::sleep_for(chrono::seconds(1));
        cout << get_syetem_cpu_usage() << endl;
        cout << get_system_mem_usage() << endl;
    }

    return 0;
}