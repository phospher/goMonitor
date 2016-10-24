package com.phospher.goMonitor.aggregator;

import org.apache.spark.api.java.JavaPairRDD;
import org.apache.spark.streaming.api.java.JavaPairDStream;
import com.phospher.goMonitor.entities.SystemInfo;
import java.io.Serializable;

public interface SystemInfoAggregator extends Serializable {

    void aggregate(JavaPairRDD<String, SystemInfo> systemInfoes) throws Exception;

    void aggregate(JavaPairDStream<String, SystemInfo> systemInfoes) throws Exception;
}