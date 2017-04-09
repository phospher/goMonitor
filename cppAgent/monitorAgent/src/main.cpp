#include "monitorAgent.h"
#include "utils/config.h"
#include "systeminfo.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <log4cpp/PropertyConfigurator.hh>
#include <log4cpp/Category.hh>

using namespace std;
using namespace log4cpp;

void init_log4cpp()
{
    PropertyConfigurator::configure("./log4cpp.conf");
}

int main(int argc, char *argv[])
{
    try
    {
        init_log4cpp();
    }
    catch (ConfigureFailure &ex)
    {
        cout << "error to load log configuration: " << ex.what() << endl;
        return -1;
    }

    Category &logger = Category::getRoot();
    logger.debug("system start");

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