#include <vector>
#include <arpa/inet.h>

using namespace std;

#define MAC_ADDRESS_LEN 18
#define PROCESS_NAME_LEN 1024
#define MESSAGE_CONTENT_LEN 4096
#define MESSAGE_TYPE_LEN 10

typedef float percent_t;

class ProcessInfo
{
public:
  percent_t CPUUsage;
  percent_t MemoryUsage;
  const char *get_process_name() const;
  void set_process_name(const char *process_name);
  const char *to_json() const;

private:
  char ProcessName[PROCESS_NAME_LEN];
};

class SystemInfo
{
public:
  SystemInfo();
  percent_t CPUUsage;
  percent_t MemoryUsage;
  time_t Time;
  vector<ProcessInfo *> ProcessInfoes;
  const char *get_ip_address() const;
  void set_ip_address(const char *ip_address);
  const char *get_mac_address() const;
  void set_mac_address(const char *mac_address);
  const char *to_json() const;
  ~SystemInfo();

private:
  char IPAddress[INET_ADDRSTRLEN];
  char MacAddress[MAC_ADDRESS_LEN];
};

class Message
{
public:
  const char *get_content() const;
  void set_content(const char *content);
  const char *get_type() const;
  void set_type(const char *type);
  const char *to_json() const;

private:
  char Content[MESSAGE_CONTENT_LEN];
  char Type[MESSAGE_TYPE_LEN];
};