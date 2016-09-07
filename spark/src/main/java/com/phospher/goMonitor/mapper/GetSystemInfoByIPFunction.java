package com.phospher.goMonitor.mapper;

import org.apache.spark.api.java.function.FlatMapFunction;
import com.phospher.goMonitor.entities.*;
import java.util.Iterator;
import com.phospher.goMonitor.inject.InjectorManager;
import com.phospher.goMonitor.data.SystemInfoRepository;

public class GetSystemInfoByIPFunction implements FlatMapFunction<String, SystemInfo> {
    
    public Iterator<SystemInfo> call(String ipAddress) throws Exception {
        SystemInfoRepository systemInfoRepository = InjectorManager.getInjector().getInstance(SystemInfoRepository.class);
        return systemInfoRepository.getSystemInfoByIP(ipAddress).iterator();
    }
}