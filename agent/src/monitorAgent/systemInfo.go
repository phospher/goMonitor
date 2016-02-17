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
		lineRegex, _ := regexp.Compile(`(([0-9]|\.)*)%? *id`)
		resultStr := lineRegex.FindSubmatch(targetLine)
		if len(resultStr) < 2 {
			return 0
		} else {
			result, _ := strconv.ParseFloat(string(resultStr[1]), 64)
			return (100 - result) / 100
		}
	} else {
		return 0
	}
}

func GetSystemMemoryUsage() float64 {
	cmd := exec.Command("top", "-bn1")
	if output, err := cmd.Output(); err == nil {
		regex, _ := regexp.Compile(`Mem: *([0-9]*)[A-Za-z]* *total, *([0-9]*)[A-Za-z]* *used`)
		resultStr := regex.FindSubmatch(output)
		if len(resultStr) < 3 {
			return 0
		} else {
			totalMem, _ := strconv.ParseFloat(string(resultStr[1]), 64)
			usedMem, _ := strconv.ParseFloat(string(resultStr[2]), 64)
			return usedMem / totalMem
		}
	} else {
		return 0
	}
}
