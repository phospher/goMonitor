#include <vector>

using namespace std;

class ProcessInfo
{
  public:
    const char *ProcessName;
    float CPUUsage;
    float MemoryUsage;
    const char *to_json() const;
}

class SystemInfo
{
  public:
    const char *MacAddress;
    float CPUUsage;
    float MemoryUsage;
    const char *IPAddress;
    int Time;
    vector<ProcessInfo &> ProcessInfo;
    const char *to_json() const;
}