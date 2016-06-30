package main

import "mainServer/service"

var services []func()

func init() {
	services = []func(){service.StartHeartbeatService, service.StartCollectSystemService}
}

func main() {
	for _, item := range services {
		item()
	}
}
