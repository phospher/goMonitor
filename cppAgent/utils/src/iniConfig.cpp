#include <unistd.h>
#include <getopt.h>
#include <iostream>
#include <string>
#include "config.h"

using namespace std;

const struct option long_option[] = {
    {"configFile", required_argument, NULL, 'c'}};

const char *short_option = "c:";

string get_default_file_path()
{
    char tmp[100];
    ssize_t r = readlink("/proc/self/exe", tmp, 100);
    tmp[r] = '\0';
    string file_path(tmp);
    size_t found = file_path.find_last_of("/");
    return file_path.substr(0, found) + "/config.ini";
}

void init_configuration(int argc, char *argv[])
{
    int opt;
    string file_path("");
    while ((opt = getopt_long(argc, argv, short_option, long_option, NULL)) != -1)
    {
        if (opt == 'c')
        {
            file_path = optarg;
            break;
        }
    }
    if (file_path.length() == 0)
    {
        file_path = get_default_file_path();
    }

    cout << file_path << endl;
}