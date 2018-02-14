#include <vector>
#include <arpa/inet.h>
#include <string>

#ifndef __UTILS_DATA_h__
#define __UTILS_DATA_h__

#define MAC_ADDRESS_LEN 18
#define PROCESS_NAME_LEN 1024
#define MESSAGE_CONTENT_LEN 4096
#define MESSAGE_TYPE_LEN 10

typedef float percent_t;

class ProcessInfo
{
public:
  ProcessInfo();
  ~ProcessInfo();
  const std::string &get_process_name() const;
  void set_process_name(const std::string &process_name);
  percent_t get_cpu_usage() const;
  void set_cpu_usage(percent_t cpu_usage);
  percent_t get_memory_usage() const;
  void set_memory_usage(percent_t memory_usage);
  std::string to_json() const;

private:
  std::string ProcessName;
  percent_t CPUUsage;
  percent_t MemoryUsage;
};

class SystemInfo
{
public:
  SystemInfo();
  const std::string &get_ip_address() const;
  void set_ip_address(const std::string &ip_address);
  const std::string &get_mac_address() const;
  void set_mac_address(const std::string &mac_address);
  percent_t get_cpu_usage() const;
  void set_cpu_usage(percent_t cpu_usage);
  percent_t get_memory_usage() const;
  void set_memory_usage(percent_t memory_usage);
  time_t get_time() const;
  void set_time(time_t time);
  std::vector<ProcessInfo *> &get_process_infoes();
  const std::vector<ProcessInfo *> &get_process_infoes() const;
  void set_process_info(int index, ProcessInfo *process_info);
  std::string to_json() const;
  ~SystemInfo();

private:
  std::string IPAddress;
  std::string MacAddress;
  percent_t CPUUsage;
  percent_t MemoryUsage;
  time_t Time;
  std::vector<ProcessInfo *> ProcessInfoes;
};

class Message
{
public:
  const char *get_content() const;
  void set_content(const char *content);
  const char *get_type() const;
  void set_type(const char *type);
  std::string to_json() const;
  Message();
  ~Message();

private:
  char Content[MESSAGE_CONTENT_LEN];
  char Type[MESSAGE_TYPE_LEN];
};

#endif