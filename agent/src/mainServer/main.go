package main

import (
	"log"
	"mainServer/filter"
	"mainServer/handler"
)

func init() {

}

func main() {
	perr := handler.AddSystemInfoFilter(filter.MySqlMachineRecordFilter{})

	perr = handler.AddSystemInfoFilter(filter.LogSystemInfoFilter{})
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
