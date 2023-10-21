package org.example;

import java.net.InetAddress;
import java.net.UnknownHostException;

public class CSDNIPAddress {
    public static void main(String[] args) throws UnknownHostException {
        InetAddress[] addresses = InetAddress.getAllByName("www.csdn.net");
        System.out.println("CSDN's IP addresses:");
        for (InetAddress address : addresses) {
            System.out.println(address.toString());
        }
    }
}
