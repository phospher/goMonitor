package persist

import (
	"log"
	"mainServer/config"

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
	connString, err := config.GetSqlDBConnectionString()
	if err != nil {
		log.Fatalln(err.Error())
	}

	driverName, err := config.GetSqlDBDriverName()
	if err != nil {
		log.Fatalln(err.Error())
	}

	engine, err = xorm.NewEngine(driverName, connString)
	if err != nil {
		log.Fatalln(err.Error())
	}

	err = engine.Sync2(new(MachineRecord))
	if err != nil {
		log.Fatalln(err.Error())
	}
}

func AddMachineRecord(machineRecord MachineRecord) error {
	searchResult := MachineRecord{IpAddress: machineRecord.IpAddress, MacAddress: machineRecord.MacAddress}
	has, err := engine.Get(&searchResult)
	if err != nil {
		return err
	}

	if has {
		_, err = engine.Update(searchResult)
		if err != nil {
			return err
		}
	} else {
		_, err = engine.Insert(machineRecord)
		if err != nil {
			return err
		}
	}

	return nil
}
