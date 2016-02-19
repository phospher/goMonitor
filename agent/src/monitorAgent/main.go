package main

import (
	"encoding/json"
	"fmt"
	"monitorAgent/config"
	"time"
	"utils"
)

func main() {
	address, err := config.GetMainServerConfig()
	if err != nil {
		fmt.Println(err.Error())
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
			fmt.Println(err.Error())
			return
		}
	}
}
