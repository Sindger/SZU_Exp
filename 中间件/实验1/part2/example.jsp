<%@ page contentType="text/HTML;charset=GB2312"%>
<%//接收数据
String username=request.getParameter("username");
String password=request.getParameter("password");
//将数据转换为汉字
username=new String(username.getBytes("8859_1"),"gb2312");
//显示数据
out.print("用户名："+username+"<br>");
out.print("密码："+password);
%>