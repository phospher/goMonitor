package com.phospher.goMonitor.reducer;

import org.apache.spark.api.java.function.Function2;
import com.phospher.goMonitor.entities.SystemInfo;
import org.apache.spark.api.java.function.Function;

public class MaxUsageSeqFunction implements Function2<Double, SystemInfo, Double> {
    
    private Function<SystemInfo, Double> valFunc;
    
    public MaxUsageSeqFunction(Function<SystemInfo, Double> valFunc) {
        this.valFunc = valFunc;
    }
    
    public Double call(Double a, SystemInfo b) throws Exception {
        double value = this.valFunc.call(b);
        return a > value ? a : value;
    }
}