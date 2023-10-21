package org.example;

import java.io.*;
import java.net.*;

public class Client {
    public static void main(String[] args) throws IOException {
        Socket socket = new Socket("localhost", 8888);
        System.out.println("已连接到服务器...");

        // 接收文件名
        InputStream is = socket.getInputStream();
        byte[] buffer = new byte[1024];
        int len = is.read(buffer);
        String fileName = new String(buffer, 0, len);

        // 接收文件内容
        FileOutputStream fos = new FileOutputStream("new_" + fileName);
        while ((len = is.read(buffer)) != -1) {
            fos.write(buffer, 0, len);
        }
        //输出接收到的文件的路径
        System.out.println("接收到的文件路径为：" + new File(fileName).getAbsolutePath());
        //输出文件保存路径
        System.out.println("文件保存路径为：" + new File("new_" + fileName).getAbsolutePath());
        fos.close();
        is.close();
        socket.close();
    }
}
