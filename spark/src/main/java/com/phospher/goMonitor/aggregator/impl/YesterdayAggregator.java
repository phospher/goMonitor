package com.phospher.goMonitor.aggregator.impl;

import org.apache.spark.api.java.JavaPairRDD;
import org.apache.spark.streaming.api.java.JavaPairDStream;
import com.phospher.goMonitor.entities.SystemInfo;
import com.phospher.goMonitor.aggregator.SystemInfoAggregator;
import java.text.SimpleDateFormat;
import java.util.Calendar;

public abstract class YesterdayAggregator implements SystemInfoAggregator {

    protected String getYesterday() {
        Calendar cal = Calendar.getInstance();
        cal.add(Calendar.DATE, -1);
        SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd");
        return format.format(cal.getTime());
    }

    public abstract void aggregate(JavaPairRDD<String, SystemInfo> systemInfoes) throws Exception;

    public abstract void aggregate(JavaPairDStream<String, SystemInfo> systemInfoes) throws Exception;
}