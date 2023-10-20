<%--
  Created by IntelliJ IDEA.
  User: Sindger
  Date: 2022/09/27
  Time: 13:40
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
  <head>
    <title>servlet 广告管理</title>
  </head>
  <body>
  <h3>上传图片</h3>
  <form>
    链接 <input type=url size=20 name=link>
    <br>
    图片 <input type=url size=20 name=image> <input type=submit value='Browse..' formaction="/showImage">
    <br>
    <input type=submit value='提交' formaction="/addBanner">
  </form>
  </body>
</html>
