package org.example;

import java.io.*;
import java.net.*;

public class Server {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8888);
        System.out.println("服务器已启动，等待客户端连接...");
        Socket socket = serverSocket.accept();
        System.out.println("客户端已连接...");

        // 发送文件名
        String fileName = "test.txt";
        OutputStream os = socket.getOutputStream();
        os.write(fileName.getBytes());
        //输出需要传输的文件路径
        System.out.println("需要传输的文件路径为：" + new File(fileName).getAbsolutePath());
        System.out.println("开始传出文件");
        // 发送文件内容
        FileInputStream fis = new FileInputStream(fileName);
        byte[] buffer = new byte[1024];
        int len;
        while ((len = fis.read(buffer)) != -1) {
            os.write(buffer, 0, len);
        }
        System.out.println("文件传输结束");
        fis.close();
        os.close();
        socket.close();
        serverSocket.close();
    }
}
