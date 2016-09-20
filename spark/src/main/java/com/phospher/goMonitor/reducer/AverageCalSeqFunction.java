package com.phospher.goMonitor.reducer;

import org.apache.spark.api.java.function.Function2;
import com.phospher.goMonitor.entities.*;
import org.apache.spark.api.java.function.Function;

public class AverageCalSeqFunction implements Function2<AverageItem, SystemInfo, AverageItem> {
    
    private Function<SystemInfo, Double> valFunc;
    
    public AverageCalSeqFunction(Function<SystemInfo, Double> valFunc) {
        this.valFunc = valFunc;
    }
    
    public AverageItem call(AverageItem a, SystemInfo b) throws Exception {
        return new AverageItem(a.getTotal() + this.valFunc.call(b), a.getCount() + 1);
    }
}