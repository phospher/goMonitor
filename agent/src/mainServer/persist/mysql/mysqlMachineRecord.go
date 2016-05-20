package mysql

import (
	"log"
	"mainServer/config"

	"mainServer/persist"

	_ "github.com/go-sql-driver/mysql"
	"github.com/go-xorm/xorm"
)

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

	err = engine.Sync2(new(persist.MachineRecord))
	if err != nil {
		log.Fatalln(err.Error())
	}

	persist.RegisterMachineRecordRepository(new(MySqlMachineRecordRepository))
}

type MySqlMachineRecordRepository struct {
}

func (o *MySqlMachineRecordRepository) AddMachineRecord(machineRecord persist.MachineRecord) error {
	searchResult := persist.MachineRecord{IpAddress: machineRecord.IpAddress, MacAddress: machineRecord.MacAddress}
	has, err := engine.Get(&searchResult)
	if err != nil {
		return err
	}

	if has {
		_, err = engine.Id(searchResult.Id).Update(searchResult)
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
