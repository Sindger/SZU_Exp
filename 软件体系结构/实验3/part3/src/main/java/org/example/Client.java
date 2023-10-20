package org.example;

public class Client {
    public static void main(String[] args) {
        Filter filter=new Sharpen();
        Image JPGImage= new JPGImage(filter);
        Image GIFImage= new GIFImage(filter);
        Image BMPImage= new BMPImage(filter);
        JPGImage.operation();
        GIFImage.operation();
        BMPImage.operation();
    }

}
