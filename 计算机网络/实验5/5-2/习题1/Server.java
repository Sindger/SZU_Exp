package org.example;

import java.awt.*;
import java.net.*;
import java.io.*;
import java.util.*;

public class Server {
    public static void main(String[] args) throws IOException{
        //监听6666端口
        ServerSocket ss = new ServerSocket(6666);
        System.out.println("Server started:"+ss);
        //等待客户端连接
        Socket s = ss.accept();
        //如果客户端连接成功，打印出来
        System.out.println("Client connected:"+s);
        //接收客户端的数据
        DataInputStream dis = new DataInputStream(s.getInputStream());
        while(true){
            String str = (String)dis.readUTF();
            System.out.println("Instruction from Client: "+str);
            switch (str){
                case "Time":
                    System.out.println("Server current time:"+new Date());
                    break;
                case "Exit":
                    //向客户端发送报文
                    System.out.println("Bye");
                    DataOutputStream dos = new DataOutputStream(s.getOutputStream());
                    dos.writeUTF("Bye");
                    dos.flush();
                    dos.close();
                    break;
                default:
                    System.out.println("message: "+str);
                    break;
            }
            if(str.equals("Exit"))
                break;
        }
        //关闭资源
        dis.close();
        s.close();
        ss.close();
    }
}
