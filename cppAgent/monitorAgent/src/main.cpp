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
        get_system_cpu_usage();
        string process_name("chrome");
        ProcessInfo *process_info = get_process_info(process_name);
        if (process_info != NULL)
        {
            cout << process_info->ProcessName << endl;
            cout << process_info->CPUUsage << endl;
        }
        this_thread::sleep_for(chrono::seconds(1));
    }

    return 0;
}