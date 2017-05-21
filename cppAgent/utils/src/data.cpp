#include "data.h"
#include "rapidjson/prettywriter.h"

using namespace rapidjson;

template <typename Writer> void serialize_processInfo(Writer& writer, const ProcessInfo* processInfo)
{
    writer.StartObject();
    writer.String("ProcessName");
    writer.String(processInfo->ProcessName);
    writer.String("CPUUsage");
    writer.Double(processInfo->CPUUsage);
    writer.String("MemoryUsage");
    writer.Double(processInfo->MemoryUsage);
    writer.EndObject();
}

const char* ProcessInfo::to_json() const
{
    StringBuffer sb;
    PrettyWriter<StringBuffer> writer(sb);
    serialize_processInfo(writer, this);
    return sb.GetString();
}

template <typename Writer> void serialize_systemInfo(Writer& writer, const SystemInfo* systemInfo)
{
    writer.StartObject();
    writer.String("MacAddress");
    writer.String(systemInfo->MacAddress);
    writer.String("CPUUsage");
    writer.Double(systemInfo->CPUUsage);
    writer.String("MemoryUsage");
    writer.Double(systemInfo->MemoryUsage);
    writer.String("IPAddress");
    writer.String(systemInfo->IPAddress);
    writer.String("Time");
    writer.Int(systemInfo->Time);
    writer.String("ProcessInfoes");
    writer.StartArray();
    for(ProcessInfo* item: systemInfo->ProcessInfoes)
    {
        serialize_processInfo(writer, item);
    }
    writer.EndArray();
    writer.EndObject();
}

const char* SystemInfo::to_json() const
{
    StringBuffer sb;
    PrettyWriter<StringBuffer> writer(sb);
    serialize_systemInfo(writer, this);
    return sb.GetString();
}