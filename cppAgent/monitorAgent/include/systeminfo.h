#include "utils/data.h"

SystemInfo &get_system_info();

percent_t get_system_cpu_usage();

vector<int32_t> *get_pid_by_name(string& name);