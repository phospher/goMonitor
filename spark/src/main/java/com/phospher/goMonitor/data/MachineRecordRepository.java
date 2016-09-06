package com.phospher.goMonitor.data;

import java.util.List;

public interface MachineRecordRepository {
    
    List<String> getMachineIpAddresses() throws Exception;
}