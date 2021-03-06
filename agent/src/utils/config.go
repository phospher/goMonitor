package utils

import (
	"flag"
	"fmt"
	"os"
	"path/filepath"

	"gopkg.in/ini.v1"
)

var configFilePath string

func init() {
	currentDir, _ := filepath.Abs(filepath.Dir(os.Args[0]))
	defaultConfigFilePath := filepath.Join(currentDir, "config.ini")
	flag.StringVar(&configFilePath, "configFile", defaultConfigFilePath, "Configuration File Path")
}

func GetConfigValue(session *ini.Section, key string) (string, error) {
	if session.HasKey(key) {
		return session.Key(key).String(), nil
	} else {
		return "", fmt.Errorf("Can not find %s configuration", key)
	}
}

func GetConfigFilePath() string {
	return configFilePath
}
