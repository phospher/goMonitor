package main

import (
	"fmt"
	"monitorAgent/config"
)

func main() {
	address, err := config.GetMainServerConfig()
	if err == nil {
		fmt.Println(address)
	} else {
		fmt.Println(err.Error())
	}
}
