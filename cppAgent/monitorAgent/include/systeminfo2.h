#include "utils/data.h"
#include "utils.h"
#include <string>
#include <memory>
#include <log4cpp/Category.hh>
#include <vector>

#ifndef __MONITORAGENT_SYSTEMINFO_h__
#define __MONITORAGENT_SYSTEMINFO_h__

class SystemInfoProvider
{
  public:
    SystemInfoProvider();
    ~SystemInfoProvider();
    SystemInfo *get_system_info();

  private:
    SystemInfo *CurrentSystemInfo;
    static log4cpp::Category &LOGGER;
};

#endif