#include <string>

using namespace std;

void init_configuration(int argc, char *argv[]);

class ConfigProvider
{
  public:
    virtual string get_config_value(const string &session, const string &key) const = 0;
};

extern const ConfigProvider* CURRENT_CONFIG_PROVIDER;