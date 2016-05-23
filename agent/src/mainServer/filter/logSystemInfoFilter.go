package filter

import (
	"mainServer/config"
	"utils"

	"gopkg.in/mgo.v2"
)

type LogSystemInfoFilter struct {
}

func (this LogSystemInfoFilter) Process(systemInfo utils.SystemInfo) (utils.SystemInfo, error) {
	connStr, err := config.GetDBConnectionString()
	if err != nil {
		return systemInfo, err
	}

	session, err := mgo.Dial(connStr)
	if err != nil {
		return systemInfo, err
	}

	collection := session.DB("Monitor").C("SystemInfo")
	return systemInfo, collection.Insert(systemInfo)
}
