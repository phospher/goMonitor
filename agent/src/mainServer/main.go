package main

import (
	"gopkg.in/mgo.v2"
	"mainServer/config"
	"utils"
)

var systemInfoChan chan *utils.SystemInfo

func init() {
	systemInfoChan = make(chan *utils.SystemInfo, 1000)
}

func main() {
	go func() {
		persistSystemInfo(<-systemInfoChan)
	}()
}

func persistSystemInfo(systemInfo *utils.SystemInfo) error {
	connStr, err := config.GetDBConnectionString()
	if err != nil {
		return err
	}

	session, err := mgo.Dial(connStr)
	if err != nil {
		return err
	}

	collection := session.DB("Monitor").C("SystemInfo")
	return collection.Insert(systemInfo)
}
