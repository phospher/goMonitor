package com.phospher.goMonitor.data.impl;

import com.phospher.goMonitor.data.SystemInfoRepository;
import com.phospher.goMonitor.configuration.ConfigProvider;
import com.phospher.goMonitor.entities.*;
import com.mongodb.*;
import org.mongodb.morphia.*;
import com.google.inject.Inject;
import java.util.*;

public class MongoDBSystemInfoRepository implements SystemInfoRepository {
    
    private ConfigProvider configProvider;
    
    @Inject
    public MongoDBSystemInfoRepository(ConfigProvider configProvider) {
        this.configProvider = configProvider;
    }
    
    public List<SystemInfo> getSystemInfoByIP(String ipAddress) {
        MongoClientURI clientURI = new MongoClientURI(this.configProvider.getMongoDBConnectionString());
        MongoClient client = new MongoClient(clientURI);
        
        Morphia morphia = new Morphia();
        morphia.mapPackage("com.phospher.goMonitor.entities", true);
        
        Calendar cal = Calendar.getInstance();
        cal.add(Calendar.DATE, -1);
        cal.set(Calendar.HOUR, 0);
        cal.set(Calendar.MINUTE, 0);
        cal.set(Calendar.SECOND, 0);
        cal.set(Calendar.MILLISECOND, 0);
        long startTime = cal.getTimeInMillis();
        
        cal.add(Calendar.DATE, 1);
        long endTime = cal.getTimeInMillis();
        
        Datastore datastore = morphia.createDatastore(client, "Monitor");
        List<SystemInfo> result = datastore.createQuery(SystemInfo.class)
            .field("IPAddress").equal(ipAddress)
            // .field("Time").greaterThanOrEq(startTime)
            // .field("Time").lessThanOrEq(endTime)
            .asList();
        return result;
    }
}