package utils

import (
	"log"
	"mainServer/config"
	"time"

	_ "github.com/go-sql-driver/mysql"
	"github.com/go-xorm/xorm"
)

func GetXormEngine() (*xorm.Engine, error) {
	connString, err := config.GetSqlDBConnectionString()
	if err != nil {
		return nil, err
	}

	driverName, err := config.GetSqlDBDriverName()
	if err != nil {
		return nil, err
	}

	engine, err := xorm.NewEngine(driverName, connString)
	if err != nil {
		log.Fatalln(err.Error())
	}

	return engine, nil
}

func CreateIntervalBackendFunc(function func(time.Time) error, interval time.Duration) func() {
	return func() {
		go func() {
			ticker := time.NewTicker(interval)
			for t := range ticker.C {
				err := function(t)
				if err != nil {
					log.Panicln(err.Error())
				}
			}
		}()
	}
}
