package persist

import (
	"mainServer/config"
	"utils"

	"gopkg.in/mgo.v2"
)

func PersistSystemInfo(systemInfo *utils.SystemInfo) error {
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
