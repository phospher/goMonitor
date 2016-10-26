package com.phospher.goMonitor.sparkStream;

import org.apache.spark.*;
import org.apache.spark.streaming.api.java.*;
import org.apache.spark.streaming.Durations;
import com.phospher.goMonitor.mapper.*;
import com.phospher.goMonitor.entities.*;
import com.phospher.goMonitor.aggregator.impl.*;

public class App {
   private static final String checkpointDir = "/tmp/checkpoint/";

    public static void main(String[] args) throws Exception {

        JavaStreamingContext sc = JavaStreamingContext.getOrCreate(checkpointDir, () -> {
            SparkConf conf = new SparkConf().setAppName("goMonitor.sparkStream");
            JavaStreamingContext context = new JavaStreamingContext(conf, Durations.seconds(1));
            JavaReceiverInputDStream<String> inputStream = context.socketTextStream("localhost", 9999);
            JavaPairDStream<String, SystemInfo> systemInfoes = inputStream.mapToPair(new GetSystemInfoByJsonFunction()).window(Durations.seconds(5)).cache();

            new AvgCPUUsageAggregator().aggregate(systemInfoes); 
            new MaxCPUUsageAggregator().aggregate(systemInfoes);
            new MinCPUUsageAggregator().aggregate(systemInfoes);
            
            context.checkpoint(checkpointDir);
            return context;
        });

        sc.start();
        sc.awaitTermination();
    }
}