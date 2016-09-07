package com.phospher.goMonitor.entities;

import org.bson.types.ObjectId;
import org.mongodb.morphia.annotations.*;

@Entity("SystemInfo")
public class SystemInfo {
    
    @Id
    private ObjectId id;
    
    @Property("MacAddress")
    private String macAddress;
    
    @Property("CPUUsage")
    private double cpuUsage;
    
    @Property("MemoryUsage")
    private double memoryUsage;
    
    @Property("IPAddress")
    private String ipAddress;
    
    @Property("Time")
    private long time;
    
    @Embedded("ProcessStates")
    private ProcessInfo[] processStates;
    
    public ObjectId getId() {
        return this.id;
    }
    
    public void setId(ObjectId id) {
        this.id = id;
    }
    
    public String getMacAddress() {
        return this.macAddress;
    }
    
    public void setMacAddress(String macAddress) {
        this.macAddress = macAddress;
    }
    
    public double getCPUUsage() {
        return this.cpuUsage;
    }
    
    public void setCPUUsage(double cpuUsage) {
        this.cpuUsage = cpuUsage;
    }
    
    public double getMemoryUsage() {
        return this.memoryUsage;
    }
    
    public void setMemoryUsage(double memoryUsage) {
        this.memoryUsage = memoryUsage;
    }
    
    public String getIPAddress() {
        return this.ipAddress;
    }
    
    public void setIPAddress(String ipAddress) {
        this.ipAddress = ipAddress;
    }
    
    public long getTime() {
        return this.time;
    }
    
    public void setTime(long time) {
        this.time = time;
    }
    
    public ProcessInfo[] getProcessStates() {
        return this.processStates;
    }
    
    public void setProcessStates(ProcessInfo[] processStates) {
        this.processStates = processStates;
    }
}