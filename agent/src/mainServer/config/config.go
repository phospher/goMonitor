package config

import (
	"utils"

	"flag"

	"gopkg.in/ini.v1"
)

const (
	DBConnectionStringValueName    = "DBConnectionString"
	PortValueName                  = "Port"
	SqlDBConnectionStringValueName = "SqlDBConnectionString"
	SqlDBDirverNameValueName       = "SqlDBDriverName"
	SparkStreamAddress             = "SparkStreamAddress"
)

func init() {
	flag.Parse()
}

func getConfigValue(valueName string) (string, error) {
	cfg, err := ini.Load(utils.GetConfigFilePath())
	if err != nil {
		return "", err
	}

	if session, err := cfg.GetSection(""); err == nil {
		return utils.GetConfigValue(session, valueName)
	} else {
		return "", err
	}
}

func GetDBConnectionString() (string, error) {
	return getConfigValue(DBConnectionStringValueName)
}

func GetListeningPort() (string, error) {
	return getConfigValue(PortValueName)
}

func GetSqlDBConnectionString() (string, error) {
	return getConfigValue(SqlDBConnectionStringValueName)
}

func GetSqlDBDriverName() (string, error) {
	return getConfigValue(SqlDBDirverNameValueName)
}

func GetSparkStreamAddress() (string, error) {
	return getConfigValue(SparkStreamAddress)
}
