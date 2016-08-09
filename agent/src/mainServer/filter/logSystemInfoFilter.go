package filter

import (
	"mainServer/config"
	"utils"

	"log"

	"gopkg.in/mgo.v2"
)

var session *mgo.Session

func init() {
	connStr, err := config.GetDBConnectionString()
	if err != nil {
		log.Fatalln(err.Error())
	}

	session, err = mgo.Dial(connStr)
	if err != nil {
		log.Fatalln(err.Error())
	}
}

type LogSystemInfoFilter struct {
}

func (this LogSystemInfoFilter) Process(systemInfo utils.SystemInfo) (utils.SystemInfo, error) {
	collection := session.DB("Monitor").C("SystemInfo")
	return systemInfo, collection.Insert(systemInfo)
}
