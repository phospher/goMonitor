#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include "systeminfo2.h"
#include "utils/data.h"
#include "utils.h"

using namespace std;

log4cpp::Category &SystemInfoProvider::LOGGER = log4cpp::Category::getRoot();

SystemInfoProvider::SystemInfoProvider() : CurrentSystemInfo(NULL) {}

SystemInfoProvider::~SystemInfoProvider()
{
    if (this->CurrentSystemInfo != NULL)
    {
        delete this->CurrentSystemInfo;
    }
}

SystemInfo *SystemInfoProvider::get_system_info()
{
    return NULL;
}