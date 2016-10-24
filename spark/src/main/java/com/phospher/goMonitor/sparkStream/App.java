package com.phospher.goMonitor.sparkStream;

import org.apache.spark.*;
import org.apache.spark.streaming.api.java.*;
import org.apache.spark.streaming.Durations;
import com.phospher.goMonitor.mapper.*;
import com.phospher.goMonitor.entities.*;
import com.phospher.goMonitor.aggregator.impl.*;

public class App {
    public static void main(String[] args) throws Exception {
        SparkConf conf = new SparkConf().setAppName("goMonitor.sparkStream");
        JavaStreamingContext sc = new JavaStreamingContext(conf, Durations.seconds(1));

        JavaReceiverInputDStream<String> inputStream = sc.socketTextStream("localhost", 9999);
        JavaPairDStream<String, SystemInfo> systemInfoes = inputStream.mapToPair(new GetSystemInfoByJsonFunction()).cache();

        new AvgCPUUsageAggregator().aggregate(systemInfoes); 


        sc.start();
        sc.awaitTermination();
    }
}