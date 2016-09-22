package com.phospher.goMonitor.reducer;

import org.apache.spark.api.java.function.Function2;

public class MinUsageCombFunction implements Function2<Double, Double, Double> {
    
    public Double call(Double a, Double b) {
        return a <= b ? a : b;
    }
}