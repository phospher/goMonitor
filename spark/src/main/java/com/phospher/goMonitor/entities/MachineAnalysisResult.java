package com.phospher.goMonitor.entities;

import com.j256.ormlite.table.DatabaseTable;
import com.j256.ormlite.field.DatabaseField;

@DatabaseTable(tableName = "machine_analysis_result")
public class MachineAnalysisResult extends MySqlEntity {

    @DatabaseField(columnName = "ip_address")
    private String ipAddress;

    @DatabaseField(columnName = "double_field")
    private double doubleField;

    @DatabaseField(columnName = "int_field")
    private int intField;

    @DatabaseField(columnName = "date")
    private String date;

    public String getIPAddress() {
        return this.ipAddress;
    }

    public void setIPAddress(String ipAddress) {
        this.ipAddress = ipAddress;
    }

    public double getDoubleField() {
        return this.doubleField;
    }

    public void setDoubleField(double doubleField) {
        this.doubleField = doubleField;
    }

    public int getIntField() {
        return this.intField;
    }

    public void setIntField(int intField) {
        this.intField = intField;
    }

    public String getDate() {
        return this.date;
    }

    public void setDate(String date) {
        this.date = date;
    }
}