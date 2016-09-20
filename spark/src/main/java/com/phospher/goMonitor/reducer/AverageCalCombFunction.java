package com.phospher.goMonitor.reducer;

import org.apache.spark.api.java.function.Function2;
import com.phospher.goMonitor.entities.AverageItem;

public class AverageCalCombFunction implements Function2<AverageItem, AverageItem, AverageItem> {
    
    public AverageItem call(AverageItem a, AverageItem b) {
        return new AverageItem(a.getTotal() + b.getTotal(), a.getCount() + b.getCount());
    }
}