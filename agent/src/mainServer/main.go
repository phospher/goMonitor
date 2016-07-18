package main

import (
	"mainServer/service"
	"mainServer/utils"
	"time"
)

var services []func()

func init() {
	services = []func(){
		utils.CreateIntervalBackendFunc(service.RunHearbeat, 5*time.Second),
		service.StartCollectSystemService,
	}
}

func main() {
	for _, item := range services {
		item()
	}
}
