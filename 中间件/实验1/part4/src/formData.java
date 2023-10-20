import java.util.*;
public class formData {
    public String name;      //表单项名称
    public String value;     //表单项的值，如果是文件，这个值是文件名
    public String contentType;     //如果是文件，这个是文件的类型，否则为NULL
    public byte[] file;      //把文件保存为字节数组
}