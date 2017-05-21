#include <vector>

using namespace std;

typedef float percent_t;

class ProcessInfo
{
public:
  const char *ProcessName;
  percent_t CPUUsage;
  percent_t MemoryUsage;
  const char *to_json() const;
};

class SystemInfo
{
public:
  SystemInfo();
  const char *MacAddress;
  percent_t CPUUsage;
  percent_t MemoryUsage;
  const char *IPAddress;
  int Time;
  vector<ProcessInfo *> ProcessInfoes;
  const char *to_json() const;
  ~SystemInfo();
};
