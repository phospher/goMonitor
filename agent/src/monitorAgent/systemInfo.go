package main

import (
	"bufio"
	"bytes"
	"fmt"
	"net"
	"os/exec"
	"regexp"
	"strconv"
)

type ProcessInfo struct {
	Pid         int
	ProcessName string
	CPUUsage    float64
	MemoryUsage float64
}

type SystemInfo struct {
	MacAddress    string
	CPUUsage      float64
	MemoryUsage   float64
	ProcessStates []ProcessInfo
}

func GetSystemInfo() SystemInfo {
	result := SystemInfo{}
	result.MacAddress = getMacAddress()
	topOutput := getTopCommandOutput()
	result.CPUUsage = getSystemCPUUsage(topOutput)
	result.MemoryUsage = getSystemMemoryUsage(topOutput)
	getProcessStates(topOutput)
	return result
}

func getMacAddress() string {
	interfaces, err := net.Interfaces()
	if err != nil {
		return err.Error()
	}
	return interfaces[1].HardwareAddr.String()
}

func getTopCommandOutput() []byte {
	cmd := exec.Command("top", "-bn1")
	if result, err := cmd.Output(); err == nil {
		return result
	} else {
		return make([]byte, 0)
	}
}

func getSystemCPUUsage(output []byte) float64 {
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
}

func getSystemMemoryUsage(output []byte) float64 {
	regex, _ := regexp.Compile(`Mem: *([0-9]*)[A-Za-z]* *total, *([0-9]*)[A-Za-z]* *used`)
	resultStr := regex.FindSubmatch(output)
	if len(resultStr) < 3 {
		return 0
	} else {
		totalMem, _ := strconv.ParseFloat(string(resultStr[1]), 64)
		usedMem, _ := strconv.ParseFloat(string(resultStr[2]), 64)
		return usedMem / totalMem
	}
}

func getProcessStates(output []byte) []byte {
	scanner := bufio.NewScanner(bytes.NewReader(output))
	scanner.Split(bufio.ScanLines)
	regex, _ := regexp.Compile(`[0-9]+.*chrome`)
	for scanner.Scan() {
		if regex.MatchString(scanner.Text()) {
			fmt.Println(scanner.Text())
		}
	}
	return make([]byte, 0)
}
