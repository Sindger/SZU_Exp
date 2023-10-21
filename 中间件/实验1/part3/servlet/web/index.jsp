<%--
  Created by IntelliJ IDEA.
  User: Sindger
  Date: 2022/9/28
  Time: 13:06
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<!DOCTYPE html>
<html>
<head>
    <title>Servlet 示例</title>
</head>
<body bgcolor="white">
<h3>Servlet 示例</h3>
<form action="/servlet" method="POST">
    姓名 <input type=text size=20 name=username>
    <br>
    密码 <input type=password size=20 name=password>
    <br>
    <input type=submit value='提交'>
</form>
</body>
</html>