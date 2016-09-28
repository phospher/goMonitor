package com.phospher.goMonitor.data.impl;

import com.phospher.goMonitor.data.MachineRecordRepository;
import com.phospher.goMonitor.configuration.ConfigProvider;
import java.util.List;
import java.util.ArrayList;
import java.sql.*;
import com.google.inject.Inject;
import com.phospher.goMonitor.entities.*;
import com.j256.ormlite.dao.*;

public class MySQLMachineRecordRepository extends MySqlRepository implements MachineRecordRepository {
        
    public List<String> getMachineIpAddresses() throws Exception {
        ArrayList<String> ipAddresses = new ArrayList<String>();
        
        for(MachineRecord item : DaoManager.createDao(this.getConnectionSource(), MachineRecord.class)) {
            ipAddresses.add(item.getIPAddress());
        }
        
        return ipAddresses;
    }
}