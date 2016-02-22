package config

import (
	"errors"
	"fmt"
	"github.com/go-ini/ini"
	"strings"
	"utils"
)

const (
	MainServerSectionName    = "MainServer"
	MainServerIpKeyName      = "IP"
	MainServerPortKeyName    = "Port"
	SystemSectionName        = "System"
	SystemConcernedProcesses = "ConcernedProcesses"
)

func GetMainServerConfig() (string, error) {
	cfg, err := ini.Load(utils.GetConfigFilePath())
	if err != nil {
		return "", err
	}

	if session, err := cfg.GetSection(MainServerSectionName); err == nil {
		ip, err := utils.GetConfigValue(session, MainServerIpKeyName)
		if err != nil {
			return "", err
		}
		port, err := utils.GetConfigValue(session, MainServerPortKeyName)
		if err != nil {
			return "", err
		}

		return fmt.Sprintf("%s:%s", ip, port), nil
	} else {
		return "", errors.New("Can not find MainServer configuration")
	}
}

func GetProcessNames() ([]string, error) {
	cfg, err := ini.Load(utils.GetConfigFilePath())
	if err != nil {
		return make([]string, 0), err
	}

	if session, err := cfg.GetSection(SystemSectionName); err == nil {
		processStr, err := utils.GetConfigValue(session, SystemConcernedProcesses)
		if err != nil {
			return make([]string, 0), err
		}
		return strings.Split(processStr, ","), nil
	} else {
		return make([]string, 0), err
	}
}
