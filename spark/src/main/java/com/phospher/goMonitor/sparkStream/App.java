package com.phospher.goMonitor.sparkStream;

import org.apache.spark.*;
import org.apache.spark.streaming.api.java.*;
import org.apache.spark.streaming.Durations;

public class App {
    public static void main(String[] args) throws Exception {
        SparkConf conf = new SparkConf().setAppName("goMonitor.sparkStream");
        JavaStreamingContext sc = new JavaStreamingContext(conf, Durations.seconds(1));

        JavaReceiverInputDStream<String> inputStream = sc.socketTextStream("localhost", 9999);
        inputStream.foreachRDD(rdd -> {
            rdd.foreach(i -> {
               System.out.println(i); 
            });
        });

        sc.start();
        sc.awaitTermination();
    }
}