package config

import (
	"errors"
	"fmt"
	"github.com/go-ini/ini"
	"os"
	"path/filepath"
)

const (
	MainServerSectionName = "MainServer"
	MainServerIpKeyName   = "IP"
	MainServerPortKeyName = "Port"
)

func GetMainServerConfig() (string, error) {
	cfg, err := ini.Load(getConfigFilePath())
	if err != nil {
		return "", err
	}

	if session, err := cfg.GetSection(MainServerSectionName); err == nil {
		ip, err := getConfigValue(session, MainServerIpKeyName)
		if err != nil {
			return "", err
		}
		port, err := getConfigValue(session, MainServerPortKeyName)
		if err != nil {
			return "", err
		}

		return fmt.Sprintf("%s:%s", ip, port), nil
	} else {
		return "", errors.New("Can not find MainServer configuration")
	}
}

func getConfigValue(session *ini.Section, key string) (string, error) {
	if session.HasKey(key) {
		return session.Key(key).String(), nil
	} else {
		return "", fmt.Errorf("Can not find %s configuration", key)
	}
}

func getConfigFilePath() string {
	dirPath, _ := filepath.Abs(filepath.Dir(os.Args[0]))
	return filepath.Join(dirPath, "config.ini")
}