package com.phospher.goMonitor.data.impl;

import com.phospher.goMonitor.data.SystemInfoRepository;
import com.phospher.goMonitor.configuration.ConfigProvider;
import com.phospher.goMonitor.entities.*;
import com.mongodb.*;
import org.mongodb.morphia.*;
import com.google.inject.Inject;
import java.util.List;

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
        
        Datastore datastore = morphia.createDatastore(client, "Monitor");
        List<SystemInfo> result = datastore.createQuery(SystemInfo.class).field("IpAddress").equal(ipAddress).asList();
        System.out.println("systeminfo count " + ipAddress + ": " + result.size());
        return result;
    }
}