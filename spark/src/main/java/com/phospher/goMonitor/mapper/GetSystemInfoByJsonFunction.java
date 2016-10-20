package com.phospher.goMonitor.mapper;

import org.apache.spark.api.java.function.PairFunction;
import com.phospher.goMonitor.entities.SystemInfo;
import scala.Tuple2;
import com.google.gson.*;
import java.lang.reflect.Field;
import org.mongodb.morphia.annotations.*;

public class GetSystemInfoByJsonFunction implements PairFunction<String, String, SystemInfo> {

    private class MonitorFieldNamingStrategy implements FieldNamingStrategy {

        public String translateName(Field field) {
            Property propertyAnnotation = field.getAnnotation(Property.class);
            if (propertyAnnotation != null) {
                return propertyAnnotation.value();
            } else {
                Embedded embeddedAnnotation = field.getAnnotation(Embedded.class);
                if (embeddedAnnotation != null) {
                    return embeddedAnnotation.value();
                } else {
                    return field.getName();
                }
            }
        }
    }

    public Tuple2<String, SystemInfo> call(String t) throws Exception {
        if (t != null && !("").equals(t)) {
            Gson gson = new GsonBuilder().setFieldNamingStrategy(new MonitorFieldNamingStrategy()).create();
            SystemInfo systemInfo = gson.fromJson(t, SystemInfo.class);
            return new Tuple2<String, SystemInfo>(systemInfo.getIPAddress(), systemInfo);
        } else {
            return null;
        }
    }
} 