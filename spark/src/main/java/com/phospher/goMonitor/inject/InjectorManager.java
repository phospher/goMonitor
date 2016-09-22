package com.phospher.goMonitor.inject;

import com.google.inject.*;

public class InjectorManager {
    
    private static Injector injector;

    public static Injector initInjector() {
        return Guice.createInjector(new SparkInjectModule());
    }
}