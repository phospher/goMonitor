package filter

import (
	"log"
	"mainServer/config"

	"utils"

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

type MySqlMachineRecordFilter struct {
}

func (this MySqlMachineRecordFilter) Process(systemInfo utils.SystemInfo) (utils.SystemInfo, error) {
	searchResult := MachineRecord{IpAddress: systemInfo.IPAddress, MacAddress: systemInfo.MacAddress}
	has, err := engine.Get(&searchResult)
	if err != nil {
		return systemInfo, err
	}

	if has {
		_, err = engine.Id(searchResult.Id).Update(searchResult)
		if err != nil {
			return systemInfo, err
		}
	} else {
		_, err = engine.Insert(MachineRecord{IpAddress: systemInfo.IPAddress, MacAddress: systemInfo.MacAddress})
		if err != nil {
			return systemInfo, err
		}
	}

	return systemInfo, nil
}
