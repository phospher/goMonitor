package com.phospher.goMonitor.data.impl;

import com.phospher.goMonitor.configuration.ConfigProvider;
import com.j256.ormlite.jdbc.JdbcPooledConnectionSource;
import com.j256.ormlite.support.ConnectionSource;
import com.google.inject.*;
import com.phospher.goMonitor.inject.InjectorManager;
import com.j256.ormlite.db.MysqlDatabaseType;

public abstract class MySqlRepository {

    private static ConnectionSource connectionSource;

    static {
        Injector injector = InjectorManager.initInjector();
        ConfigProvider configProvider = injector.getInstance(ConfigProvider.class);

        try {
        connectionSource = new JdbcPooledConnectionSource(configProvider.getMySQLConnectionString(), 
            configProvider.getMySQLUserName(), configProvider.getMySQLPassword(), new MysqlDatabaseType());
        } catch(Exception ex) {
            throw new ExceptionInInitializerError(ex);
        }
    }

    protected ConnectionSource getConnectionSource() {
        return connectionSource;
    }
}