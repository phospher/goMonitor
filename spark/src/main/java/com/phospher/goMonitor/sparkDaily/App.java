package com.phospher.goMonitor.sparkDaily;

import org.apache.spark.api.java.*;
import org.apache.spark.SparkConf;
import java.util.*;
import com.google.inject.*;
import com.phospher.goMonitor.inject.*;
import com.phospher.goMonitor.data.MachineRecordRepository;
import com.phospher.goMonitor.mapper.*;
import org.apache.spark.api.java.function.VoidFunction;
import com.phospher.goMonitor.entities.*;
import scala.Tuple2;
import com.phospher.goMonitor.reducer.*;
import java.text.SimpleDateFormat;
import com.phospher.goMonitor.aggregator.impl.*;

public class App {
    public static void main(String[] args) throws Exception {
        SparkConf conf = new SparkConf().setAppName("goMonitor.SparkDaily");
        JavaSparkContext context = new JavaSparkContext(conf);
        
        Injector injector = InjectorManager.initInjector();
        MachineRecordRepository machineRecordRepository = injector.getInstance(MachineRecordRepository.class);
        List<String> ipAddress = machineRecordRepository.getMachineIpAddresses();
        
        JavaRDD<String> ipRDD = context.parallelize(ipAddress);
        JavaPairRDD<String, SystemInfo> systemInfoRDD = ipRDD.flatMap(new GetSystemInfoByIPFunction())
            .mapToPair(i -> new Tuple2(i.getIPAddress(), i)).cache();

        new MaxCPUUsageAggregator().aggregate(systemInfoRDD);

        new MinCPUUsageAggregator().aggregate(systemInfoRDD);

        new AvgCPUUsageAggregator().aggregate(systemInfoRDD);
    }
}
