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
import scala.Tuple2;
import com.phospher.goMonitor.reducer.*;

public class App {
    public static void main(String[] args) throws Exception {
        SparkConf conf = new SparkConf().setAppName("goMonitor.SparkDaily");
        JavaSparkContext context = new JavaSparkContext(conf);
        
        Injector injector = InjectorManager.initInjector();
        MachineRecordRepository machineRecordRepository =injector.getInstance(MachineRecordRepository.class);
        List<String> ipAddress = machineRecordRepository.getMachineIpAddresses();
        
        JavaRDD<String> ipRDD = context.parallelize(ipAddress);
        JavaPairRDD<String, SystemInfo> systemInfoRDD = ipRDD.flatMap(new GetSystemInfoByIPFunction())
            .mapToPair(i -> new Tuple2(i.getIPAddress(), i)).cache();
        
        JavaPairRDD<String, Double> maxRDD = systemInfoRDD.aggregateByKey(-1d, 
            new MaxUsageSeqFunction(a -> a.getCPUUsage()), new MaxUsageCombFunction());
        maxRDD.foreach(a -> System.out.printf("max result: %s %f\n", a._1, a._2));
        
        JavaPairRDD<String, Double> minRDD = systemInfoRDD.aggregateByKey(999d, 
            new MinUsageSeqFunction(a -> a.getCPUUsage()), new MinUsageCombFunction());
        minRDD.foreach(a -> System.out.printf("min result: %s %f\n", a._1, a._2));
        
        AverageItem zero = new AverageItem();
        JavaPairRDD<String, AverageItem> avgRDD = systemInfoRDD.aggregateByKey(zero, 
            new AverageCalSeqFunction(a -> a.getCPUUsage()), new AverageCalCombFunction());
        avgRDD.foreach(a -> System.out.printf("avg result: %s %f %d\n", a._1, a._2.getTotal(), a._2.getCount()));
    }
}
