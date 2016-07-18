package service

import (
	"mainServer/utils"

	"log"

	"time"

	"mainServer/message"

	"fmt"

	"mainServer/dataEntity"

	_ "github.com/go-sql-driver/mysql"
	"github.com/go-xorm/xorm"
)

var engine *xorm.Engine

const heartbeatInterval = 5 * time.Second

func init() {
	var err error
	engine, err = utils.GetXormEngine()
	if err != nil {
		log.Fatalln(err.Error())
	}

	message.InitSendAlertHelper(new(message.LogSendAlertHelper))
}

func RunHearbeat(t time.Time) error {
	var machines []dataEntity.MachineRecord
	engine.Where("last_updated_at < ?", t.Unix()-5).Find(&machines)
	if machines != nil && len(machines) > 0 {
		for _, item := range machines {
			alertMsg := new(message.AlertMessage)
			alertMsg.Content = fmt.Sprintf("%s(%s) is offine", item.IpAddress, item.MacAddress)
			message.SendAlert(alertMsg)
		}
	}
	return nil
}
