package main

import (
	"bufio"
	"bytes"
	"monitorAgent/config"
	"net"
	"os/exec"
	"regexp"
	"strconv"
	"strings"
	"time"
	"utils"
)

func GetSystemInfo() (utils.SystemInfo, error) {
	result := utils.SystemInfo{}
	if processNames, err := config.GetProcessNames(); err == nil {
		result.MacAddress = getMacAddress()
		topOutput := getTopCommandOutput()
		result.CPUUsage = getSystemCPUUsage(topOutput)
		result.MemoryUsage = getSystemMemoryUsage(topOutput)
		result.ProcessStates = getProcessStates(topOutput, processNames)
		result.IPAddress = getIPAddress()
		result.Time = time.Now().Unix()
		return result, nil
	} else {
		return result, err
	}
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
		return -1
	} else {
		result, _ := strconv.ParseFloat(string(resultStr[1]), 64)
		return (100 - result) / 100
	}
}

func getSystemMemoryUsage(output []byte) float64 {
	regex, _ := regexp.Compile(`Mem *: *([0-9]*)[A-Za-z]* *total, *([0-9]*)[A-Za-z]* *free, *([0-9]*)[A-Za-z]* *used`)
	resultStr := regex.FindSubmatch(output)
	if len(resultStr) < 3 {
		return -1
	} else {
		totalMem, _ := strconv.ParseFloat(string(resultStr[1]), 64)
		usedMem, _ := strconv.ParseFloat(string(resultStr[3]), 64)
		return usedMem / totalMem
	}
}

func getProcessStates(output []byte, processNames []string) []*utils.ProcessInfo {
	scanner := bufio.NewScanner(bytes.NewReader(output))
	scanner.Split(bufio.ScanLines)
	regex, _ := regexp.Compile(`^ *[0-9]+.*`)
	whitespaceRegex, _ := regexp.Compile(`\s+`)
	result := make(map[string]*utils.ProcessInfo)
	for scanner.Scan() {
		text := scanner.Text()
		if regex.MatchString(text) {
			textItems := whitespaceRegex.Split(text, -1)
			if isTargetProcess(processNames, textItems[12]) {
				_, ok := result[textItems[12]]
				if !ok {
					result[textItems[12]] = &utils.ProcessInfo{ProcessName: textItems[12], CPUUsage: 0, MemoryUsage: 0}
				}
				cpuUsage, _ := strconv.ParseFloat(textItems[9], 64)
				memoryUsage, _ := strconv.ParseFloat(textItems[10], 64)
				result[textItems[12]].CPUUsage += cpuUsage
				result[textItems[12]].MemoryUsage += memoryUsage
			}
		}
	}
	return getProcessInfoFromMap(result)
}

func isTargetProcess(processNames []string, processName string) bool {
	for _, item := range processNames {
		if item == processName {
			return true
		}
	}

	return false
}

func getProcessInfoFromMap(processInfo map[string]*utils.ProcessInfo) []*utils.ProcessInfo {
	result := make([]*utils.ProcessInfo, 0)
	for _, item := range processInfo {
		result = append(result, item)
	}
	return result
}

func getIPAddress() string {
	ifaces, err := net.InterfaceAddrs()
	if err != nil {
		return ""
	}

	var ipAddress string
	for _, item := range ifaces {
		ipAddress = strings.Split(item.String(), "/")[0]

		if ipAddress != "::1" && ipAddress != "127.0.0.1" {
			break
		}
	}
	return ipAddress
}
