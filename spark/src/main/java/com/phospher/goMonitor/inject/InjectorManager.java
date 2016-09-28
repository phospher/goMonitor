package com.phospher.goMonitor.inject;

import com.google.inject.*;

public class InjectorManager {
    
    private static Injector injector;

    public static Injector initInjector() {
        if(injector == null) {
            injector = Guice.createInjector(new SparkInjectModule()); 
        }
        return injector;
    }
}