package com.phospher.goMonitor.entities;

import java.io.Serializable;

public class AverageItem implements Serializable {
    
    private double total;
    private long count;
    
    public AverageItem() {
        this(0, 0);
    }
    
    public AverageItem(double total, long count) {
        this.total = total;
        this.count = count;
    }
    
    public double getTotal() {
        return this.total;
    }
    
    public void setTotal(double total) {
        this.total = total;
    }
    
    public long getCount() {
        return this.count;
    }
    
    public void setCount(long count) {
        this.count = count;
    }
}