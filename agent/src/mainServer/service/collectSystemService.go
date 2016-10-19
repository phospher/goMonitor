package service

import (
	"log"
	"mainServer/filter"
	"mainServer/handler"
)

func StartCollectSystemService() {
	perr := handler.AddSystemInfoFilter(filter.MySqlMachineRecordFilter{})

	perr = handler.AddSystemInfoFilter(filter.LogSystemInfoFilter{})

	perr = handler.AddSystemInfoFilter(filter.SendToSparkFilter{})
	if perr != nil {
		log.Fatalln(perr)
	}

	networkHandler := handler.NewNetworkHandler()
	networkHandler.StartPersitMessage()

	err := networkHandler.StartNetwork()
	if err != nil {
		log.Fatalln(err)
	}
}
