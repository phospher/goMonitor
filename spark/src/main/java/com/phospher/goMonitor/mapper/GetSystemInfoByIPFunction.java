package com.phospher.goMonitor.mapper;

import org.apache.spark.api.java.function.FlatMapFunction;
import com.phospher.goMonitor.entities.*;
import java.util.Iterator;

public class GetSystemInfoByIPFunction implements FlatMapFunction<String, SystemInfo> {
    
    public Iterator<SystemInfo> call(String ipAddress) throws Exception {
        return null;
    }
}