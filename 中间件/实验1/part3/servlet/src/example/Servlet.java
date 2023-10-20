package example;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.io.PrintWriter;

public class Servlet extends HttpServlet{
    public void doGet(HttpServletRequest request,
                      HttpServletResponse response) throws IOException, ServletException {
        System.out.println("hasgsfkhfl");
        response.setContentType("text/html;charset=gb2312");
//使用response的out对象输出HTML文件头
        PrintWriter out = response.getWriter();
        out.println("<html>");
        out.println("<body>");
        out.println("<head>");
        out.println("<title>Servlet 示例</title>");
        out.println("</head>");
        out.println("<body color=\"white\">");
        out.println("<h3>Servlet 示例</h3>");
//接收客户端请求中传来的数据
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if(username != null){//转换为中文字符集
            username = new String(username.getBytes("8859_1"),"gb2312");
        }
        out.println("<br>");
//将取到的数据输出到页面中
        if(username != null || password != null){
            out.println("用户名为:");
            out.println(username + "<br>");
            out.println("密码为：");
            out.println(password);
        }
//再在输出页面中产生一个表单接收用户再输入姓名和密码信息
        out.println("<form action=\"servlet\" method=POST>");
        out.println("用户名");
        out.println("<input type=text size=20 name=username>");
        out.println("<br>");
        out.println("密码");
        out.println("<input type=password size=20 name=password>");
        out.println("<br>");
        out.println("<input type=submit value='提交'>");
        out.println("</form>");
        out.println("</body>");
        out.println("</html>");
    }
    //doPost方法的处理与doGet一致，则对post请求的处理与get请求一致
    public void doPost(HttpServletRequest request,
                       HttpServletResponse response)throws IOException, ServletException{
        System.out.println("sbcmmxv");
        doGet(request, response);
    }
}
