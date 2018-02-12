#include "utils/data.h"
#include "utils.h"
#include <string>
#include <memory>
#include <log4cpp/Category.hh>
#include <vector>
#include "processinfo.h"

#ifndef __MONITORAGENT_SYSTEMINFO_h__
#define __MONITORAGENT_SYSTEMINFO_h__

class SystemInfoProvider
{
public:
  SystemInfoProvider();
  std::shared_ptr<SystemInfo> get_system_info();

private:
  std::shared_ptr<SystemInfo> CurrentSystemInfo;
  static log4cpp::Category &LOGGER;
  std::string init_ip_address() const;
  void init_mac_address(const std::string &net_name);
  CPUTime LastSystemCPUTime;
  int32_t SystemWorkTimeDiff;
  std::vector<ProcessInfoProvider*> ProcessInfoProviders;

  percent_t get_system_cpu_usage();
  std::string get_system_cpu_stat();
  percent_t get_system_mem_usage();
  void get_system_mem_info(int32_t *total_mem, int32_t *available_mem);
  // ProcessInfo *get_process_info(std::string &process_name);
};

#endif