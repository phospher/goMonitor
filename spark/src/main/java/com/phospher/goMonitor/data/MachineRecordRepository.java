package com.phospher.goMonitor.data;

import java.util.List;
import com.phospher.goMonitor.entities.*;

public interface MachineRecordRepository {
    
    List<String> getMachineIpAddresses() throws Exception;

    void addMachineAnalysisResult(MachineAnalysisResult machineAnalysisResult) throws Exception;
}