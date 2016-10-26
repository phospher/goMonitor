package com.phospher.goMonitor.aggregator.impl;

import org.apache.spark.api.java.*;
import org.apache.spark.streaming.api.java.*;
import com.phospher.goMonitor.entities.SystemInfo;
import com.phospher.goMonitor.reducer.*;
import com.phospher.goMonitor.data.MachineRecordRepository;
import com.phospher.goMonitor.entities.MachineAnalysisResult;
import com.phospher.goMonitor.inject.InjectorManager;

public class MaxCPUUsageAggregator extends YesterdayAggregator {

    public MaxCPUUsageAggregator() {
        super();
    }

    @Override
    public void aggregate(JavaPairRDD<String, SystemInfo> systemInfoes) throws Exception {
        JavaPairRDD<String, Double> maxRDD = systemInfoes.aggregateByKey(-1d, 
            new MaxUsageSeqFunction(a -> a.getCPUUsage()), new MaxUsageCombFunction());

        maxRDD.foreach(i -> {
            MachineAnalysisResult result = new MachineAnalysisResult();
            result.setIPAddress(i._1);
            result.setDoubleField(i._2);
            result.setDate(this.getYesterday());
            result.setResultType("MAX");
            MachineRecordRepository respository = InjectorManager.initInjector().getInstance(MachineRecordRepository.class);
            respository.addMachineAnalysisResult(result);
            System.out.printf("max result: %s %f\n", i._1, i._2);
        });
    }

    @Override
    public void aggregate(JavaPairDStream<String, SystemInfo> systemInfoes) throws Exception {
        systemInfoes.updateStateByKey((values, state) -> {
            if (values != null && values.size() > 0) {
                double max = state.isPresent() ? (double)state.get() : -1d;
                for (SystemInfo item : values) {
                    if (item.getCPUUsage() > max) {
                        max = item.getCPUUsage();
                    }
                }

                return Optional.of(max);
            } else {
                return state;
            }
        }).foreachRDD(rdd -> {
            rdd.foreach(i -> System.out.printf("max result: %s %f\n", i._1, i._2));
        });
    }
}
