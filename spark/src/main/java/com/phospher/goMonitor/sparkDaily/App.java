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
        
        JavaPairRDD<String, Double> maxRDD = systemInfoRDD.aggregateByKey(-1d, 
            new MaxUsageSeqFunction(a -> a.getCPUUsage()), new MaxUsageCombFunction());
        
        String yesterday = getYesterday();
        maxRDD.foreach(i -> {
            MachineAnalysisResult result = new MachineAnalysisResult();
            result.setIPAddress(i._1);
            result.setDoubleField(i._2);
            result.setDate(yesterday);
            result.setResultType("MAX");
            MachineRecordRepository respository = InjectorManager.initInjector().getInstance(MachineRecordRepository.class);
            respository.addMachineAnalysisResult(result);
            System.out.printf("max result: %s %f\n", i._1, i._2);
        });
        
        JavaPairRDD<String, Double> minRDD = systemInfoRDD.aggregateByKey(999d, 
            new MinUsageSeqFunction(a -> a.getCPUUsage()), new MinUsageCombFunction());
        minRDD.foreach(i -> {
            MachineAnalysisResult result = new MachineAnalysisResult();
            result.setIPAddress(i._1);
            result.setDoubleField(i._2);
            result.setDate(yesterday);
            result.setResultType("MIN");
            MachineRecordRepository respository = InjectorManager.initInjector().getInstance(MachineRecordRepository.class);
            respository.addMachineAnalysisResult(result);
            System.out.printf("min result: %s %f\n", i._1, i._2);
        });
        
        AverageItem zero = new AverageItem();
        JavaPairRDD<String, AverageItem> avgRDD = systemInfoRDD.aggregateByKey(zero, 
            new AverageCalSeqFunction(a -> a.getCPUUsage()), new AverageCalCombFunction());
        avgRDD.foreach(i -> {
            MachineAnalysisResult result = new MachineAnalysisResult();
            result.setIPAddress(i._1);
            result.setDoubleField(i._2.getTotal());
            result.setLongField(i._2.getCount());
            result.setDate(yesterday);
            result.setResultType("AVG");
            MachineRecordRepository respository = InjectorManager.initInjector().getInstance(MachineRecordRepository.class);
            respository.addMachineAnalysisResult(result);
            System.out.printf("avg result: %s %f %d\n", i._1, i._2.getTotal(), i._2.getCount());
        });
    }

    private static String getYesterday() {
        Calendar cal = Calendar.getInstance();
        cal.add(Calendar.DATE, -1);
        SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd");
        return format.format(cal.getTime());
    }
}
