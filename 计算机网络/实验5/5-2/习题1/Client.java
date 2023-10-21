package org.example;

import java.awt.*;
import java.net.*;
import java.io.*;
import java.util.*;

public class Client {
    public static void main(String[] args) throws Exception{
        Scanner sc = new Scanner(System.in);
        //连接到本机的6666端口
        Socket s = new Socket("localhost",6666);
        //向本机的6666端口发送数据
        DataOutputStream dos = new DataOutputStream(s.getOutputStream());
        System.out.println("Client connected:"+s);
        while(true){
            System.out.print("Client: ");
            String str = sc.nextLine();
            dos.writeUTF(str);
            if (str.equals("Exit")){
                //接受服务器端的数据
                DataInputStream dis = new DataInputStream(s.getInputStream());
                System.out.println("Server: "+dis.readUTF());
                dis.close();
                break;
            }
        }
        //关闭资源
        dos.flush();
        dos.close();
        s.close();
    }
}
