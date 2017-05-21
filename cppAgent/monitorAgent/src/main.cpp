#include "monitorAgent.h"
#include "utils/config.h"
#include "systeminfo.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <log4cpp/PropertyConfigurator.hh>
#include <log4cpp/Category.hh>
#include <algorithm>
#include <unistd.h>

using namespace std;
using namespace log4cpp;

string get_application_path()
{
    char tmp_path[1024];
    char path_buff[1024];
    sprintf(tmp_path, "/proc/%d/exe", getpid());
    int bytes = min((int)readlink(tmp_path, path_buff, 1024), 1023);
    if (bytes >= 0)
    {
        path_buff[bytes] = '\0';
    }
    string result(path_buff);
    return result;
}

void init_log4cpp()
{
    string app_path = get_application_path();
    cout << app_path << endl;
    if (app_path.length() == 0)
    {
        app_path = ".";
    }
    else
    {
        app_path = app_path.substr(0, app_path.find_last_of('/'));
    }
    cout << app_path << endl;
    PropertyConfigurator::configure(app_path + "/log4cpp.conf");
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
        SystemInfo *system_info = get_system_info();
        cout << system_info->to_json() << endl;
        const char *ip_address = system_info->IPAddress;
        cout << ip_address << endl;
        delete system_info;
        this_thread::sleep_for(chrono::seconds(1));
    }

    return 0;
}