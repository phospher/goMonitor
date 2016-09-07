package com.phospher.goMonitor.configuration;

public interface ConfigProvider {
    
    String getMySQLConnectionString();
    
    String getMySQLUserName();
    
    String getMySQLPassword();
    
    String getMongoDBConnectionString();
}