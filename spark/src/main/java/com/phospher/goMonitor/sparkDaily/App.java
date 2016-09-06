package com.phospher.goMonitor.sparkDaily;

import org.apache.spark.api.java.JavaSparkContext;
import org.apache.spark.SparkConf;
import java.util.List;
import com.google.inject.*;
import com.phospher.goMonitor.inject.SparkInjectModule;
import com.phospher.goMonitor.data.MachineRecordRepository;

public class App {
    public static void main(String[] args) throws Exception {
        SparkConf conf = new SparkConf().setAppName("goMonitor.SparkDaily");
        JavaSparkContext context = new JavaSparkContext(conf);
        
        Injector injector = Guice.createInjector(new SparkInjectModule());
        MachineRecordRepository machineRecordRepository = injector.getInstance(MachineRecordRepository.class);
        List<String> ipAddress = machineRecordRepository.getMachineIpAddresses();
        System.out.println("data count: " + ipAddress.size());
    }
}
