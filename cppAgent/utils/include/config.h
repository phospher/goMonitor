#include <string>

void init_configuration(int argc, char *argv[]);

class ConfigProvider
{
  public:
    virtual std::string get_config_value(const std::string &session, const std::string &key) const = 0;
};

extern const ConfigProvider* CURRENT_CONFIG_PROVIDER;