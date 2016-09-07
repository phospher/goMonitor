package com.phospher.goMonitor.configuration.impl;

import com.phospher.goMonitor.configuration.ConfigProvider;

public class HardCodeConfigProvider implements ConfigProvider {
    
    public String getMySQLConnectionString() {
        return "jdbc:mysql://localhost/Monitor";
    }
    
    public String getMySQLUserName() {
        return "monitor";
    }
    
    public String getMySQLPassword() {
        return "123456";
    }
    
    public String getMongoDBConnectionString() {
        return "mongodb://localhost";
    }
}