#include "monitorAgent.h"
#include "utils/config.h"
#include "utils/data.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <log4cpp/PropertyConfigurator.hh>
#include <log4cpp/Category.hh>

using namespace std;
using namespace log4cpp;

Category &LOGGER = Category::getRoot();

int init_socket()
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        throw runtime_error(strerror(errno));
    }

    sockaddr_in addr;
    bzero(&addr, sizeof(sockaddr_in));
    string ip = CURRENT_CONFIG_PROVIDER->get_config_value("MainServer", "IP");
    uint16_t port = (uint16_t)stoi(CURRENT_CONFIG_PROVIDER->get_config_value("MainServer", "Port").c_str());
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    addr.sin_port = htons(port);
    if (connect(fd, (sockaddr *)(&addr), sizeof(sockaddr)) < 0)
    {
        throw runtime_error(strerror(errno));
    }

    LOGGER << Priority::DEBUG << "success connect to server: " << ip << ":" << port;

    return fd;
}

void send_message(const char *message)
{
    int sockFd = init_socket();
    if (write(sockFd, message, strlen(message)) < 0)
    {
        throw runtime_error(strerror(errno));
    }

    if (close(sockFd) < 0)
    {
        throw runtime_error(strerror(errno));
    }
}
