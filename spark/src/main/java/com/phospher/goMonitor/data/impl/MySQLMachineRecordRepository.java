package com.phospher.goMonitor.data.impl;

import com.phospher.goMonitor.data.MachineRecordRepository;
import com.phospher.goMonitor.configuration.ConfigProvider;
import java.util.List;
import java.util.ArrayList;
import java.sql.*;
import com.google.inject.Inject;

public class MySQLMachineRecordRepository implements MachineRecordRepository {
    
    private ConfigProvider configProvider;
    
    @Inject
    public MySQLMachineRecordRepository(ConfigProvider configProvider) {
        this.configProvider = configProvider;
    }
    
    public List<String> getMachineIpAddresses() throws Exception {
        Class.forName("com.mysql.jdbc.Driver");
        Connection conn = DriverManager.getConnection(this.configProvider.getMySQLConnectionString(), 
            this.configProvider.getMySQLUserName(), this.configProvider.getMySQLPassword());
        Statement stmt = conn.createStatement();
        ResultSet rs = stmt.executeQuery("select ip_address from machine_record");
        ArrayList<String> ipAddresses = new ArrayList<String>();
        while(rs.next()) {
            ipAddresses.add(rs.getString("ip_address"));
        }
        
        return ipAddresses;
    }
}