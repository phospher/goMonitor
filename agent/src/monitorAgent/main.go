package main

import (
	"encoding/json"
	"fmt"
	"log"
	"monitorAgent/config"
	"time"
	"utils"
)

func main() {
	address, err := config.GetMainServerConfig()
	fmt.Printf("Connected to main server: %s\n", address)
	if err != nil {
		log.Fatalln(err)
		return
	}

	ticker := time.NewTicker(time.Second)

	for range ticker.C {
		message := utils.Message{Type: "INFO"}
		if systemInfo, err := GetSystemInfo(); err == nil {
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
