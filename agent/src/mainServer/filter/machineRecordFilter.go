package filter

import (
	"log"

	"utils"

	mainServerUtils "mainServer/utils"

	"mainServer/dataEntity"

	_ "github.com/go-sql-driver/mysql"
	"github.com/go-xorm/xorm"
)

var engine *xorm.Engine

func init() {
	var err error
	engine, err = mainServerUtils.GetXormEngine()
	if err != nil {
		log.Fatalln(err.Error())
	}
}

type MySqlMachineRecordFilter struct {
}

func (this MySqlMachineRecordFilter) Process(systemInfo utils.SystemInfo) (utils.SystemInfo, error) {
	searchResult := dataEntity.MachineRecord{IpAddress: systemInfo.IPAddress, MacAddress: systemInfo.MacAddress}
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
		_, err = engine.Insert(dataEntity.MachineRecord{IpAddress: systemInfo.IPAddress, MacAddress: systemInfo.MacAddress})
		if err != nil {
			return systemInfo, err
		}
	}

	return systemInfo, nil
}
