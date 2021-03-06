#include <string>
#include <memory>
#include <vector>

#ifndef __MONITORAGENT_UTILS_h__
#define __MONITORAGENT_UTILS_h__

class CPUTime
{
  public:
    CPUTime(int32_t work_time, int32_t total_time);
    int32_t get_work_time() const;
    int32_t get_total_time() const;
    void set_work_time(int32_t work_time);
    void set_total_time(int32_t total_time);

  private:
    int32_t WorkTime;
    int32_t TotalTime;
};

std::shared_ptr<std::vector<std::string>> split_string_by_whitspace2(const std::string &str);

void split_string2(const std::string &str, std::vector<std::string> &result, const std::string &sep);

#endif