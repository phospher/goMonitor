package com.phospher.goMonitor.inject;

import com.google.inject.AbstractModule;
import com.phospher.goMonitor.configuration.ConfigProvider;
import com.phospher.goMonitor.configuration.impl.HardCodeConfigProvider;
import com.phospher.goMonitor.data.*;
import com.phospher.goMonitor.data.impl.*;

public class SparkInjectModule extends AbstractModule {
    @Override
    protected void configure() {
        this.bind(ConfigProvider.class).to(HardCodeConfigProvider.class);
        this.bind(MachineRecordRepository.class).to(MySQLMachineRecordRepository.class);
        this.bind(SystemInfoRepository.class).to(MongoDBSystemInfoRepository.class);
    }
}