package main

import (
	"net"
	"os/exec"
	"regexp"
	"strconv"
)

func GetMacAddress() string {
	interfaces, err := net.Interfaces()
	if err != nil {
		return err.Error()
	}
	return interfaces[1].HardwareAddr.String()
}

func GetSystemCPUUsage() float64 {
	cmd := exec.Command("top", "-bn1")
	if output, err := cmd.Output(); err == nil {
		regex, _ := regexp.Compile(`%?Cpu\(s\).*id`)
		targetLine := regex.Find(output)
		lineRegex, _ := regexp.Compile(`(([0-9]|\.)*)%? id`)
		resultStr := lineRegex.FindSubmatch(targetLine)
		if len(resultStr) < 2 {
			return 0
		} else {
			result, _ := strconv.ParseFloat(string(resultStr[1]), 64)
			return result
		}
	} else {
		return 0
	}
}
