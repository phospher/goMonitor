#include "utils/data.h"
#include "utils.h"
#include <string>
#include <memory>
#include <log4cpp/Category.hh>
#include <vector>

#ifndef __MONITORAGENT_PROCESSINFO_h__
#define __MONITORAGENT_PROCESSINFO_h__

class ProcessInfoProvider
{
public:
  ProcessInfoProvider(const std::string &process_name);
  ProcessInfo *get_process_info(const int32_t total_mem, const int32_t available_mem,
                                const int32_t system_work_time_diff);
  ~ProcessInfoProvider();

private:
  const std::string ProcessName;
  static log4cpp::Category &LOGGER;
  CPUTime *LastCPUTime = NULL;

  std::shared_ptr<std::vector<int32_t>> get_pid_by_name();
  std::shared_ptr<std::vector<std::string>> get_process_stat(int32_t pid);
  int32_t get_process_cpu_time(std::vector<std::string> &process_stat);
  float get_process_mem(std::vector<std::string> &process_stat);
  percent_t cal_proces_cpu_usage(int32_t cpu_time, const int32_t system_work_time_diff);
};

#endif