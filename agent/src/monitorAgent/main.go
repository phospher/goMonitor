package main

import (
	"encoding/json"
	"log"
	"monitorAgent/config"
	"time"
	"utils"
)

func main() {
	address, err := config.GetMainServerConfig()
	if err != nil {
		log.Fatalln(err.Error())
		return
	}

	for {
		message := utils.Message{Type: "INFO"}
		if systemInfo, err := GetSystemInfo(); err == nil {
			messageContent, _ := json.Marshal(systemInfo)
			message.Content = string(messageContent)
			utils.SendMessage(address, &message)
			time.Sleep(time.Second)
		} else {
			log.Fatalln(err.Error())
			return
		}
	}
}
