import java.io.*;
import java.sql.*;
import java.text.*;
import java.util.*;
import jakarta.servlet.*;
import jakarta.servlet.http.*;

public class showBanner extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws IOException, ServletException {
        try{
            Class.forName("com.mysql.jdbc.Driver");
            String sConnStr = "jdbc:mysql://localhost/test?user=root&password"
                    + "=&useUnicode=true&characterEncoding=8859_1";
            Connection conn = DriverManager.getConnection(sConnStr);
            String sql="select id,link from banner where link!='' and type !='' and file!=''";
            Statement stmt=conn.createStatement();
            ResultSet rs=stmt.executeQuery(sql);
            rs.last();
            Random r=new Random();
            int selectedbanner=Math.abs((r.nextInt())%(rs.getRow()));
            int i=0;
            int id=0;
            String link="";

            rs.absolute(1);
            while(true){
                if(selectedbanner==i++){
                    id=rs.getInt("id");
                    link=rs.getString("link");
                    break;
                }
                rs.next();
            }
            rs.close();
            stmt.close();
            conn.close();
            response.setContentType("text/html;charset=gb2312");
            PrintWriter out=response.getWriter();
            out.print("<a href='"+link+"'><img border=0 src='showImage?id="+id+"'></a>");
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    public void doPost(HttpServletRequest request,HttpServletResponse response)
            throws IOException,ServletException{
        doGet(request, response);
    }
}
