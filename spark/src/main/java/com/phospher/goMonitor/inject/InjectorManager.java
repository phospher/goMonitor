package com.phospher.goMonitor.inject;

import com.google.inject.*;

public class InjectorManager {
    
    private static Injector injector;
    
    public static void setInjector(Injector newInjector) {
        InjectorManager.injector = newInjector;
    }
    
    public static Injector getInjector() {
        return InjectorManager.injector;
    }
}