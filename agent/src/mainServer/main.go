package main

import (
	"log"
	"mainServer/handler"
	"mainServer/persist"
	_ "mainServer/persist/mongodb"
	_ "mainServer/persist/mysql"
)

func main() {
	machineRecordRepository, err := persist.NewMachineRepository()
	if err != nil {
		log.Fatalln(err.Error())
	}

	systemInfoRepository, err := persist.NewSystemInfoRepository()
	if err != nil {
		log.Fatalln(err.Error())
	}

	networkHandler := handler.NewNetworkHandler(machineRecordRepository, systemInfoRepository)
	networkHandler.StartPersitMessage()

	err = networkHandler.StartNetwork()
	if err != nil {
		log.Fatalln(err)
	}
}
