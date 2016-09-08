package com.phospher.goMonitor.sparkDaily;

import org.apache.spark.api.java.*;
import org.apache.spark.SparkConf;
import java.util.List;
import com.google.inject.*;
import com.phospher.goMonitor.inject.*;
import com.phospher.goMonitor.data.MachineRecordRepository;
import com.phospher.goMonitor.mapper.*;
import org.apache.spark.api.java.function.VoidFunction;
import com.phospher.goMonitor.entities.*;

public class App {
    public static void main(String[] args) throws Exception {
        SparkConf conf = new SparkConf().setAppName("goMonitor.SparkDaily");
        JavaSparkContext context = new JavaSparkContext(conf);
        
        InjectorManager.setInjector(Guice.createInjector(new SparkInjectModule()));
        MachineRecordRepository machineRecordRepository = InjectorManager.getInjector().getInstance(MachineRecordRepository.class);
        List<String> ipAddress = machineRecordRepository.getMachineIpAddresses();
        
        JavaRDD<String> ipRDD = context.parallelize(ipAddress);
        System.out.println(ipRDD.flatMap(new GetSystemInfoByIPFunction()).count());
    }
}
