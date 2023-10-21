import net.sf.json.JSONArray;
import net.sf.json.JSONObject;
import java.util.ArrayList;
import java.util.List;

public class JSONtoJAVA {
    public static void javaObjToJSONstr() {
        Student stu=new Student();
        stu.setName("方依依");
        stu.setAge(19);
        JSONObject json=JSONObject.fromObject(stu);
        String jsonStr1=json.toString();
        System.out.println(jsonStr1);
    }
    public static void javaArrToJSONstr() {
        List<Student> stu=new ArrayList<Student>();
        Student s1=new Student();
        s1.setName("张欣杰");
        s1.setAge(20);
        stu.add(s1);
        Student s2=new Student();
        s2.setName("李欣杰");
        s2.setAge(21);
        stu.add(s2);
        Student s3=new Student();
        s3.setName("王欣杰");
        s3.setAge(22);
        stu.add(s3);
        JSONArray json=JSONArray.fromObject(stu);
        String jsonStr2=json.toString();
        System.out.println(jsonStr2);
    }
    public static void jsonStrTojavaObj() {
        String jsonStr = "{\"name\":\"方依依\",\"age\":17}";
        JSONObject jsonObj = JSONObject.fromObject(jsonStr);
        Student student = (Student) JSONObject.toBean(jsonObj,Student.class);
        System.out.println(student);
    }
    public static void jsonStrToJavaArry() {
        String jsonStr = "[{\"name\":\"何立立\",\"age\":\"21\"}," +
                "{\"name\":\"赵多多\",\"age\":\"22\"}]";
        JSONArray jsonArr = JSONArray.fromObject(jsonStr);
        List<Student> students = (List<Student>) JSONArray.toCollection
                (jsonArr, Student.class);
        for (Student s : students) {
            System.out.println(s);
        }
    }
    public static void main(String[] args) {
        javaObjToJSONstr();
        javaArrToJSONstr();
        jsonStrTojavaObj();
        jsonStrToJavaArry();
    }
}
