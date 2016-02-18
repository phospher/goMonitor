package main

import (
	"fmt"
	//"monitorAgent/config"
)

func main() {
	if result, err := GetSystemInfo(); err == nil {
		fmt.Println(result)
		for _, item := range result.ProcessStates {
			fmt.Println(item)
		}
	} else {
		fmt.Println(err.Error())
	}
}
