package com.phospher.goMonitor.entities;

import org.mongodb.morphia.annotations.*;
import java.io.Serializable;

public class ProcessInfo implements Serializable {
    
    @Property("ProcessName")
    private String processName;
    
    @Property("MemoryUsage")
    private double memoryUsage;
    
    @Property("CPUUsage")
    private double cpuUsage;
    
    public String getProcessName() {
        return this.processName;
    }
    
    public void setProcessName(String processName) {
        this.processName = processName;
    }
    
    public double getMemoryUsage() {
        return this.memoryUsage;
    }
    
    public void setMemoryUsage(double memoryUsage) {
        this.memoryUsage = memoryUsage;
    }
    
    public double getCPUUsage() {
        return this.cpuUsage;
    }
    
    public void setCPUUsage(double cpuUsage) {
        this.cpuUsage = cpuUsage;
    }
}