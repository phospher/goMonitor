#include <string>

#ifndef __UTILS_CONFIG_h__
#define __UTILS_CONFIG_h__

void init_configuration(int argc, char *argv[]);

class ConfigProvider
{
public:
  virtual std::string get_config_value(const std::string &session, const std::string &key) const = 0;
};

extern const ConfigProvider *CURRENT_CONFIG_PROVIDER;

#endif