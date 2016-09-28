package com.phospher.goMonitor.entities;

import com.j256.ormlite.table.TableUtils;
import com.phospher.goMonitor.inject.InjectorManager;
import com.google.inject.*;
import com.phospher.goMonitor.configuration.ConfigProvider;
import com.j256.ormlite.jdbc.JdbcConnectionSource;
import java.sql.SQLException;
import java.io.IOException;
import com.j256.ormlite.db.MysqlDatabaseType;

public abstract class MySqlEntity {

    static {
        Injector injector = InjectorManager.initInjector();
        ConfigProvider configProvider = injector.getInstance(ConfigProvider.class);

        try {
        JdbcConnectionSource connectionSource = new JdbcConnectionSource(configProvider.getMySQLConnectionString(),
            configProvider.getMySQLUserName(), configProvider.getMySQLPassword(), new MysqlDatabaseType());

        TableUtils.createTableIfNotExists(connectionSource, MachineAnalysisResult.class);
        TableUtils.createTableIfNotExists(connectionSource, MachineRecord.class);

        connectionSource.close();
        } catch(SQLException | IOException ex) { 
            throw new ExceptionInInitializerError(ex);
        }
    }
}