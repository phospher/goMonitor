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
        systemInfoes.updateStateByKey((values, state) -> {
            if (values != null) {
                long count = (state.isPresent() ? ((AverageItem)state.get()).getCount() : 0) + values.size();
                double total = (state.isPresent() ? ((AverageItem)state.get()).getTotal() : 0);
                for(SystemInfo item : values) {
                    total += item.getCPUUsage();
                }

                return Optional.of(new AverageItem(total, count));
            } else {
                return state;
            }
        }).foreachRDD(rdd -> {
            rdd.foreach(i -> System.out.printf("avg result: %s %f %d\n", i._1, ((AverageItem)i._2).getTotal(), ((AverageItem)i._2).getCount()));
        });
    }
}