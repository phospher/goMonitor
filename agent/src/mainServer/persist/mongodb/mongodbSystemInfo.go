package mongodb

import (
	"mainServer/config"
	"utils"

	"mainServer/persist"

	"gopkg.in/mgo.v2"
)

type MongoDBSystemInfoRepository struct {
}

func (o *MongoDBSystemInfoRepository) PersistSystemInfo(systemInfo *utils.SystemInfo) error {
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

func init() {
	persist.RegisterSystemInfoRepository(new(MongoDBSystemInfoRepository))
}
