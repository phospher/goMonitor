package utils

type ProcessInfo struct {
	ProcessName string `ProcessName`
	CPUUsage    float64 `CPUUsage`
	MemoryUsage float64 `MemoryUsage`
}

type SystemInfo struct {
	MacAddress    string `MacAddress`
	CPUUsage      float64 `CPUUsage`
	MemoryUsage   float64 `MemoryUsage`
	ProcessStates []*ProcessInfo `ProcessStates`
}
