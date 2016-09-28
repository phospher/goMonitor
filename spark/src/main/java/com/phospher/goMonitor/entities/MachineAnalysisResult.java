package com.phospher.goMonitor.entities;

import com.j256.ormlite.table.DatabaseTable;
import com.j256.ormlite.field.DatabaseField;

@DatabaseTable(tableName = "machine_analysis_result")
public class MachineAnalysisResult extends MySqlEntity {

    @DatabaseField(columnName = "ip_address")
    private String ipAddress;

    @DatabaseField(columnName = "double_field")
    private double doubleField;

    @DatabaseField(columnName = "long_field")
    private long longField;

    @DatabaseField(columnName = "result_type")
    private String resultType;

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

    public long getLongField() {
        return this.longField;
    }

    public void setLongField(long longField) {
        this.longField = longField;
    }

    public String getResultType() {
        return this.resultType;
    }

    public void setResultType(String resultType) {
        this.resultType = resultType;
    }

    public String getDate() {
        return this.date;
    }

    public void setDate(String date) {
        this.date = date;
    }
}