package monitorAgent

import (
	"fmt"
)

const (
	MainServerSectionName = "MainServer"
	MainServerIpKeyName   = "IP"
	MainServerPortKeyName = "Port"
)

func main() {
	address, err := GetMainServerConfig()
	if err == nil {
		fmt.Println(address)
	} else {
		fmt.Println(err.Error())
	}
}
