package com.phospher.goMonitor.data;

import com.phospher.goMonitor.entities.*;
import java.util.List;

public interface SystemInfoRepository {
    
    List<SystemInfo> getSystemInfoByIP(String ipAddress);
}