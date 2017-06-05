#include "data.h"
#include "rapidjson/prettywriter.h"
#include <cstring>

using namespace rapidjson;

template <typename Writer>
void serialize_processInfo(Writer &writer, const ProcessInfo *processInfo)
{
    writer.StartObject();
    writer.String("ProcessName");
    writer.String(processInfo->get_process_name());
    writer.String("CPUUsage");
    writer.Double(processInfo->CPUUsage);
    writer.String("MemoryUsage");
    writer.Double(processInfo->MemoryUsage);
    writer.EndObject();
}

const char *ProcessInfo::get_process_name() const
{
    return this->ProcessName;
}

void ProcessInfo::set_process_name(const char *process_name)
{
    strcpy(this->ProcessName, process_name);
}

const char *ProcessInfo::to_json() const
{
    StringBuffer sb;
    PrettyWriter<StringBuffer> writer(sb);
    serialize_processInfo(writer, this);
    const char *json = sb.GetString();
    char *result = new char[strlen(json)];
    strcpy(result, json);
    return result;
}

template <typename Writer>
void serialize_systemInfo(Writer &writer, const SystemInfo *systemInfo)
{
    writer.StartObject();
    writer.String("MacAddress");
    writer.String(systemInfo->get_mac_address());
    writer.String("CPUUsage");
    writer.Double(systemInfo->CPUUsage);
    writer.String("MemoryUsage");
    writer.Double(systemInfo->MemoryUsage);
    writer.String("IPAddress");
    writer.String(systemInfo->get_ip_address());
    writer.String("Time");
    writer.Int64((int64_t)systemInfo->Time);
    writer.String("ProcessInfoes");
    writer.StartArray();
    for (ProcessInfo *item : systemInfo->ProcessInfoes)
    {
        serialize_processInfo(writer, item);
    }
    writer.EndArray();
    writer.EndObject();
}

const char *SystemInfo::to_json() const
{
    StringBuffer sb;
    PrettyWriter<StringBuffer> writer(sb);
    serialize_systemInfo(writer, this);
    const char *json = sb.GetString();
    char *result = new char[strlen(json)];
    strcpy(result, json);
    return result;
}

SystemInfo::SystemInfo() : CPUUsage(0), MemoryUsage(0), Time(0)
{
}

const char *SystemInfo::get_ip_address() const
{
    return this->IPAddress;
}

void SystemInfo::set_ip_address(const char *ip_address)
{
    strcpy(this->IPAddress, ip_address);
}

const char *SystemInfo::get_mac_address() const
{
    return this->MacAddress;
}

void SystemInfo::set_mac_address(const char *mac_address)
{
    strcpy(this->MacAddress, mac_address);
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