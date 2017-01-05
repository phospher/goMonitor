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
    string process_name = "chrome";
    vector<int32_t> *result = get_pid_by_name(process_name);
    for (int32_t item : *result)
    {
        cout << item << endl;
    }
    delete result;

    return 0;
}