<%@ page contentType="text/HTML;charset=GB2312"%>
<%//��������
String username=request.getParameter("username");
String password=request.getParameter("password");
//������ת��Ϊ����
username=new String(username.getBytes("8859_1"),"gb2312");
//��ʾ����
out.print("�û�����"+username+"<br>");
out.print("���룺"+password);
%>