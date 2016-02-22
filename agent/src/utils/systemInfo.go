package utils

type ProcessInfo struct {
	ProcessName string
	CPUUsage    float64
	MemoryUsage float64
}

type SystemInfo struct {
	MacAddress    string
	CPUUsage      float64
	MemoryUsage   float64
	ProcessStates []*ProcessInfo
}
