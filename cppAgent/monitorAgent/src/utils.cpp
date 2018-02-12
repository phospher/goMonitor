#include "utils.h"
#include <string>
#include <memory>
#include <vector>
#include <cstring>

using namespace std;

CPUTime::CPUTime(int32_t work_time, int32_t total_time)
    : WorkTime(work_time), TotalTime(total_time)
{
}

int32_t CPUTime::get_total_time() const
{
    return this->TotalTime;
}

void CPUTime::set_total_time(int32_t total_time)
{
    this->TotalTime = total_time;
}

int32_t CPUTime::get_work_time() const
{
    return this->WorkTime;
}

void CPUTime::set_work_time(int32_t work_time)
{
    this->WorkTime = work_time;
}

shared_ptr<vector<string>> split_string_by_whitspace2(const string &str)
{
    vector<string> *result = new vector<string>;
    char *pch = strtok((char *)str.c_str(), " \t\n");
    while (pch != NULL)
    {
        result->push_back(string(pch));
        pch = strtok(NULL, " \t\n");
    }
    return shared_ptr<vector<string>>(result);
}

void split_string2(const string &str, std::vector<std::string> &result, const string &sep)
{
    std::string::size_type pos1, pos2;
    pos2 = str.find(sep);
    pos1 = 0;
    while (std::string::npos != pos2)
    {
        result.push_back(str.substr(pos1, pos2 - pos1));

        pos1 = pos2 + sep.size();
        pos2 = str.find(sep, pos1);
    }
    if (pos1 != str.length())
        result.push_back(str.substr(pos1));
}