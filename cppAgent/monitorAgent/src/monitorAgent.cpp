#include <iostream>
#include "monitorAgent.h"
#include "utils/config.h"
#include "utils/data.h"

using namespace std;

void test()
{
    cout << "hello world" << endl;
    cout << CURRENT_CONFIG_PROVIDER->get_config_value("", "PORT") << endl;
}

