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

	ticker := time.NewTicker(time.Second)

	for t := range ticker.C {
		message := utils.Message{Type: "INFO"}
		if systemInfo, err := GetSystemInfo(t); err == nil {
			messageContent, err := json.Marshal(systemInfo)
			if err != nil {
				log.Fatalln(err)
			}
			message.Content = string(messageContent)
			utils.SendMessage(address, &message)
		} else {
			ticker.Stop()
			log.Fatalln(err)
			return
		}
	}
}
