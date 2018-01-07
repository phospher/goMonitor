#include "utils/data.h"

SystemInfo *get_system_info();

percent_t get_system_cpu_usage();

ProcessInfo *get_process_info(std::string &process_name);