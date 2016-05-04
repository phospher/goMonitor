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
		log.Fatalln(err)
		return
	}

	for {
		message := utils.Message{Type: "INFO"}
		if systemInfo, err := GetSystemInfo(); err == nil {
			messageContent, err := json.Marshal(systemInfo)
			if err != nil {
				log.Fatalln(err)
			}
			message.Content = string(messageContent)
			utils.SendMessage(address, &message)
			time.Sleep(time.Second)
		} else {
			log.Fatalln(err)
			return
		}
	}
}
