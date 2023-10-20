package jni;

public class Main {
    public static void main(String[] args) {
        System.load("C:\\Users\\Sindger\\Desktop\\" +
                "JniDemo\\src\\native\\DLL.dll");
        Demo demo=new Demo();
        demo.sayHello(3,4);
    }
}
