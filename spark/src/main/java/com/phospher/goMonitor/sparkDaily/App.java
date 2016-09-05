package com.phospher.goMonitor.sparkDaily;

import org.apache.spark.api.java.JavaSparkContext;
import org.apache.spark.SparkConf;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.Statement;
import java.sql.ResultSet;
import java.util.ArrayList;
import scala.Tuple2;

/**
 * Hello world!
 *
 */
public class App {
    public static void main(String[] args) throws Exception {
        SparkConf conf = new SparkConf().setAppName("goMonitor.SparkDaily");
        JavaSparkContext context = new JavaSparkContext(conf);
        
        Class.forName("com.mysql.jdbc.Driver");
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/Monitor", "monitor", "123456");
        Statement stmt = conn.createStatement();
        ResultSet rs = stmt.executeQuery("select ip_address from machine_record");
        ArrayList<String> ipAddresses = new ArrayList<String>();
        while(rs.next()) {
            ipAddresses.add(rs.getString("ip_address"));
        }
    }
}
