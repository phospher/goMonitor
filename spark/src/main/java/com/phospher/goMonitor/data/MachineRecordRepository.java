package com.phospher.goMonitor.data;

import java.util.List;
import com.phospher.goMonitor.entities.*;
import java.io.Serializable;

public interface MachineRecordRepository extends Serializable {
    
    List<String> getMachineIpAddresses() throws Exception;

    void addMachineAnalysisResult(MachineAnalysisResult machineAnalysisResult) throws Exception;
}