package com.phospher.goMonitor.aggregator.impl;

import org.apache.spark.api.java.*;
import org.apache.spark.streaming.api.java.*;
import com.phospher.goMonitor.entities.SystemInfo;
import com.phospher.goMonitor.reducer.*;
import com.phospher.goMonitor.data.MachineRecordRepository;
import com.phospher.goMonitor.entities.*;
import com.phospher.goMonitor.inject.InjectorManager;
import scala.Tuple2;

public class AvgCPUUsageAggregator extends YesterdayAggregator {

    public AvgCPUUsageAggregator() {
        super();
    }

    @Override
    public void aggregate(JavaPairRDD<String, SystemInfo> systemInfoes) throws Exception {
        AverageItem zero = new AverageItem();
        JavaPairRDD<String, AverageItem> avgRDD = systemInfoes.aggregateByKey(zero, 
            new AverageCalSeqFunction(a -> a.getCPUUsage()), new AverageCalCombFunction());
        avgRDD.foreach(i -> {
            MachineAnalysisResult result = new MachineAnalysisResult();
            result.setIPAddress(i._1);
            result.setDoubleField(i._2.getTotal());
            result.setLongField(i._2.getCount());
            result.setDate(this.getYesterday());
            result.setResultType("AVG");
            MachineRecordRepository respository = InjectorManager.initInjector().getInstance(MachineRecordRepository.class);
            respository.addMachineAnalysisResult(result);
            System.out.printf("avg result: %s %f %d\n", i._1, i._2.getTotal(), i._2.getCount());
        });
    }

    @Override
    public void aggregate(JavaPairDStream<String, SystemInfo> systemInfoes) throws Exception {
        systemInfoes.mapToPair(i -> new Tuple2<String, AverageItem>(i._1, new AverageItem(i._2.getCPUUsage(), 1)))
            .reduceByKey((a, b) -> new AverageItem(a.getTotal() + b.getTotal(), a.getCount() + b.getCount()))
            .foreachRDD(rdd -> rdd.foreach(i -> {
                System.out.printf("avg result: %s %f %d\n", i._1, i._2.getTotal(), i._2.getCount());
            }));
    }
}