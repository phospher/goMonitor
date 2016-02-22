package config

import (
	"github.com/go-ini/ini"
	"utils"
)

const (
	DBConnectionStringValueName = "DBConnectionString"
)

func GetDBConnectionString() (string, error) {
	cfg, err := ini.Load(utils.GetConfigFilePath())
	if err != nil {
		return "", err
	}

	if session, err := cfg.GetSection(""); err == nil {
		return utils.GetConfigValue(session, DBConnectionStringValueName)
	} else {
		return "", err
	}
}
