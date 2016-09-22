package com.phospher.goMonitor.reducer;

import org.apache.spark.api.java.function.Function2;
import org.apache.spark.api.java.function.Function;
import com.phospher.goMonitor.entities.SystemInfo;

public class MinUsageSeqFunction implements Function2<Double, SystemInfo, Double> {
    
    private Function<SystemInfo, Double> valFunc;
    
    public MinUsageSeqFunction(Function<SystemInfo, Double> valFunc) {
        this.valFunc = valFunc;
    }
    
    public Double call(Double a, SystemInfo b) throws Exception {
        double value = this.valFunc.call(b);
        return a <= value ? a : value;
    }
}