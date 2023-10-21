package org.example;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.URL;
import java.net.URLConnection;

public class DownloadSZUHomePage {
    public static void main(String[] args) throws IOException {
            URL url = new URL("https://www.szu.edu.cn");
            URLConnection conn = url.openConnection();
            InputStream inputStream = conn.getInputStream();
            FileOutputStream outputStream = new FileOutputStream("szu.html");
            int bytesRead = -1;
            byte[] buffer = new byte[1024];
            int totalBytesRead = 0;
            while ((bytesRead = inputStream.read(buffer)) != -1) {
                totalBytesRead += bytesRead;
            }
            inputStream.close();
            File file = new File("szu.html");
            System.out.println("得到的文件大小: " + totalBytesRead/1024.00 + " K");
    }
}
