package com.phospher.goMonitor.entities;

import com.j256.ormlite.table.DatabaseTable;
import com.j256.ormlite.field.DatabaseField;
import com.j256.ormlite.field.DataType;
import java.util.Date;

@DatabaseTable(tableName = "machine_record")
public class MachineRecord extends MySqlEntity {

    @DatabaseField(columnName = "id", id = true)
    private long id;

    @DatabaseField(columnName = "ip_address")
    private String ipAddress;

    @DatabaseField(columnName = "mac_address")
    private String macAddresss;

    @DatabaseField(columnName = "created_at")
    private Date createdAt;

    @DatabaseField(columnName = "last_updated_at")
    private Date lastUpdatedAt;

    public long getId() {
        return this.id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public String getIPAddress() {
        return this.ipAddress;
    }

    public void setIPAddress(String ipAddress) {
        this.ipAddress = ipAddress;
    }

    public String getMacAddress() {
        return this.macAddresss;
    }

    public void setMacAddress(String macAddresss) {
        this.macAddresss = macAddresss;
    }

    public Date getCreatedAt() {
        return this.createdAt;
    }

    public void setCreatedAt(Date createdAt) {
        this.createdAt = createdAt;
    }

    public Date getLastUpdatedAt() {
        return this.lastUpdatedAt;
    }

    public void setLastUpdatedAt(Date lastUpdatedAt) {
        this.lastUpdatedAt = lastUpdatedAt;
    }
}