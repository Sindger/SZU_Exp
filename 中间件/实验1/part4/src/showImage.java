import java.io.*;
import java.sql.*;
import java.text.*;
import java.util.*;
import jakarta.servlet.*;
import jakarta.servlet.http.*;

public class showImage extends HttpServlet{
    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws IOException, ServletException {
        try{
            String id=request.getParameter("id");
            Class.forName("com.mysql.jdbc.Driver");
            String sConnStr = "jdbc:mysql://localhost/test?user=root&password"
                    + "=&useUnicode=true&characterEncoding=8859_1";
            Connection conn= DriverManager.getConnection(sConnStr);
            String sql="select type,file from banner where id="+id;
            Statement stmt=conn.createStatement();
            ResultSet rs=stmt.executeQuery(sql);
            InputStream in=null;
            if(rs.next())
                in=rs.getBinaryStream("file");
            response.setContentType(rs.getString("type"));
            ServletOutputStream sout=response.getOutputStream();
            byte b[]=new byte[1024];
            while(in.read(b)!=-1){
                sout.write(b);
            }
            sout.flush();
            sout.close();
            rs.close();
            stmt.close();
            conn.close();
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    public void doPost(HttpServletRequest request,HttpServletResponse response)
            throws IOException,ServletException{
        doGet(request, response);
    }
}
