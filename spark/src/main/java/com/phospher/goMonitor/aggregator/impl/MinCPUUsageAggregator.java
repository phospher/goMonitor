package com.phospher.goMonitor.aggregator.impl;

import org.apache.spark.api.java.*;
import org.apache.spark.streaming.api.java.JavaPairDStream;
import com.phospher.goMonitor.entities.SystemInfo;
import com.phospher.goMonitor.reducer.*;
import com.phospher.goMonitor.data.MachineRecordRepository;
import com.phospher.goMonitor.entities.MachineAnalysisResult;
import com.phospher.goMonitor.inject.InjectorManager;

public class MinCPUUsageAggregator extends YesterdayAggregator {

    public MinCPUUsageAggregator() {
        super();
    }

    @Override
    public void aggregate(JavaPairRDD<String, SystemInfo> systemInfoes) throws Exception {
        JavaPairRDD<String, Double> minRDD = systemInfoes.aggregateByKey(999d, 
            new MinUsageSeqFunction(a -> a.getCPUUsage()), new MinUsageCombFunction());
        minRDD.foreach(i -> {
            MachineAnalysisResult result = new MachineAnalysisResult();
            result.setIPAddress(i._1);
            result.setDoubleField(i._2);
            result.setDate(this.getYesterday());
            result.setResultType("MIN");
            MachineRecordRepository respository = InjectorManager.initInjector().getInstance(MachineRecordRepository.class);
            respository.addMachineAnalysisResult(result);
            System.out.printf("min result: %s %f\n", i._1, i._2);
        });
    }

    @Override
    public void aggregate(JavaPairDStream<String, SystemInfo> systemInfoes) throws Exception {
        systemInfoes.updateStateByKey((values, state) -> {
            if (values != null && values.size() > 0) {
                double min = state.isPresent() ? (double)state.get() : 9999d;
                for (SystemInfo item : values) {
                    if (item.getCPUUsage() < min) {
                        min = item.getCPUUsage();
                    }
                }

                return Optional.of(min);
            } else {
                return state;
            }
        }).foreachRDD(rdd -> {
            rdd.foreach(i -> System.out.printf("min result: %s %f\n", i._1, i._2));
        });
    }
}