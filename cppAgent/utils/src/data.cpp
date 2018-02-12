#include "data.h"
#include "rapidjson/writer.h"
#include <cstring>

using namespace rapidjson;
using namespace std;

template <typename Writer>
void serialize_processInfo(Writer &writer, const ProcessInfo *processInfo)
{
    writer.StartObject();
    writer.String("ProcessName");
    writer.String(processInfo->get_process_name().c_str());
    writer.String("CPUUsage");
    writer.Double(processInfo->get_cpu_usage());
    writer.String("MemoryUsage");
    writer.Double(processInfo->get_memory_usage());
    writer.EndObject();
}

const string &ProcessInfo::get_process_name() const
{
    return this->ProcessName;
}

void ProcessInfo::set_process_name(const string &process_name)
{
    this->ProcessName = process_name;
}

percent_t ProcessInfo::get_cpu_usage() const
{
    return this->CPUUsage;
}

void ProcessInfo::set_cpu_usage(percent_t cpu_usage)
{
    this->CPUUsage = cpu_usage;
}

percent_t ProcessInfo::get_memory_usage() const
{
    return this->MemoryUsage;
}

void ProcessInfo::set_memory_usage(percent_t memory_usage)
{
    this->MemoryUsage = memory_usage;
}

string ProcessInfo::to_json() const
{
    StringBuffer sb;
    Writer<StringBuffer> writer(sb);
    serialize_processInfo(writer, this);
    const char *json = sb.GetString();
    return string(json);
}

ProcessInfo::ProcessInfo()
{
}

ProcessInfo::~ProcessInfo()
{
}

template <typename Writer>
void serialize_systemInfo(Writer &writer, const SystemInfo *systemInfo)
{
    writer.StartObject();
    writer.String("MacAddress");
    writer.String(systemInfo->get_mac_address().c_str());
    writer.String("CPUUsage");
    writer.Double(systemInfo->get_cpu_usage());
    writer.String("MemoryUsage");
    writer.Double(systemInfo->get_memory_usage());
    writer.String("IPAddress");
    writer.String(systemInfo->get_ip_address().c_str());
    writer.String("Time");
    writer.Int64((int64_t)systemInfo->get_time());
    writer.String("ProcessInfoes");
    writer.StartArray();
    for (ProcessInfo *item : systemInfo->get_process_infoes())
    {
        serialize_processInfo(writer, item);
    }
    writer.EndArray();
    writer.EndObject();
}

string SystemInfo::to_json() const
{
    StringBuffer sb;
    Writer<StringBuffer> writer(sb);
    serialize_systemInfo(writer, this);
    const char *json = sb.GetString();
    return string(json);
}

SystemInfo::SystemInfo() : CPUUsage(0), MemoryUsage(0), Time(0)
{
}

const string &SystemInfo::get_ip_address() const
{
    return this->IPAddress;
}

void SystemInfo::set_ip_address(const string &ip_address)
{
    this->IPAddress = ip_address;
}

const string &SystemInfo::get_mac_address() const
{
    return this->MacAddress;
}

void SystemInfo::set_mac_address(const string &mac_address)
{
    this->MacAddress = mac_address;
}

percent_t SystemInfo::get_cpu_usage() const
{
    return this->CPUUsage;
}

void SystemInfo::set_cpu_usage(percent_t cpu_usage)
{
    this->CPUUsage = cpu_usage;
}

percent_t SystemInfo::get_memory_usage() const
{
    return this->MemoryUsage;
}

void SystemInfo::set_memory_usage(percent_t memory_usage)
{
    this->MemoryUsage = memory_usage;
}

time_t SystemInfo::get_time() const
{
    return this->Time;
}

void SystemInfo::set_time(time_t time)
{
    this->Time = time;
}

vector<ProcessInfo *> &SystemInfo::get_process_infoes()
{
    return this->ProcessInfoes;
}

const vector<ProcessInfo *> &SystemInfo::get_process_infoes() const
{
    return this->ProcessInfoes;
}

SystemInfo::~SystemInfo()
{
    for (ProcessInfo *item : this->ProcessInfoes)
    {
        if (item)
        {
            delete item;
        }
    }
}

const char *Message::get_content() const
{
    return this->Content;
}

void Message::set_content(const char *content)
{
    strcpy(this->Content, content);
}

const char *Message::get_type() const
{
    return this->Type;
}

void Message::set_type(const char *type)
{
    strcpy(this->Type, type);
}

string Message::to_json() const
{
    StringBuffer sb;
    Writer<StringBuffer> writer(sb);
    writer.StartObject();
    writer.String("Type");
    writer.String(this->Type);
    writer.String("Content");
    writer.String(this->Content);
    writer.EndObject();
    const char *json = sb.GetString();
    return string(json);
}

Message::Message()
{
}

Message::~Message()
{
}