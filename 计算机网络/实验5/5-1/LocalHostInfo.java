package org.example;

import java.net.InetAddress;
import java.net.UnknownHostException;

public class LocalHostInfo {
    public static void main(String[] args) throws UnknownHostException {
        InetAddress localHost = InetAddress.getLocalHost();
        String hostName = localHost.getHostName();
        String hostAddress = localHost.getHostAddress();
        System.out.println("本机名: " + hostName);
        System.out.println("本机IP地址: " + hostAddress);
    }
}
