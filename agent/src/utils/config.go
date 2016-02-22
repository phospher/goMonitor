package utils

import (
	"fmt"
	"github.com/go-ini/ini"
	"os"
	"path/filepath"
)

func GetConfigValue(session *ini.Section, key string) (string, error) {
	if session.HasKey(key) {
		return session.Key(key).String(), nil
	} else {
		return "", fmt.Errorf("Can not find %s configuration", key)
	}
}

func GetConfigFilePath() string {
	dirPath, _ := filepath.Abs(filepath.Dir(os.Args[0]))
	return filepath.Join(dirPath, "config.ini")
}
