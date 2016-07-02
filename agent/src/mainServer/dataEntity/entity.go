package dataEntity

import (
	"log"
	mainServerUtils "mainServer/utils"

	_ "github.com/go-sql-driver/mysql"
	"github.com/go-xorm/xorm"
)

type MachineRecord struct {
	Id            int64
	IpAddress     string
	MacAddress    string
	CreatedAt     int64 `xorm:"created"`
	LastUpdatedAt int64 `xorm:"updated"`
}

var engine *xorm.Engine

func init() {
	engine, err := mainServerUtils.GetXormEngine()
	if err != nil {
		log.Fatalln(err.Error())
	}

	err = engine.Sync2(new(MachineRecord))
	if err != nil {
		log.Fatalln(err.Error())
	}
}
