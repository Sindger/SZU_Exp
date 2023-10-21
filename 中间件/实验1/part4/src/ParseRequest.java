import java.util.*;
import java.io.*;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.ServletInputStream;
import jakarta.servlet.ServletException;


public class ParseRequest extends HttpServlet {
    private String ContentType="";
    private String CharacterEncoding="";

    public void setContentType(String s){
        ContentType=s;
        int j;
        if((j=ContentType.indexOf("boundary="))!=-1){
            ContentType=ContentType.substring(j+9);
            ContentType="--"+ContentType;
        }
    }

    public void setCharacterEncoding(String s){
        CharacterEncoding=s;
    }

    public Vector getFormData(HttpServletRequest req)
            throws ServletException, IOException {
        setCharacterEncoding(req.getCharacterEncoding());
        setContentType(req.getContentType());
        return getFormData(req.getInputStream());
    }

    public Vector getFormData(ServletInputStream servletinputstream)
            throws ServletException, IOException{
        Vector formdatas=new Vector();
        formData fd=null;
        int size=2048000;
        byte[] buffer=new byte[size];
        int bufferLength=0;
        byte temp[];
        byte Linebyte[]=new byte[4096];
        int ai[]=new int[1];
        int ai1[]=new int[1];

        String line;
        String boundary="----";
        String itemname="";
        String filename="";
        StringBuffer sb=new StringBuffer("");
        boolean nameflag=false;
        boolean fileflag=false;
        int skipline=0;
        int i;

        while((line=readLine(Linebyte,ai,servletinputstream,CharacterEncoding))!=null){
            if((i=line.indexOf("boundary=--"))>=0){
                boundary=line.substring(i+10);
                continue;
            }
            if(!nameflag&&!fileflag){
                itemname=getName(line);
                if(itemname!=null&&itemname!=""){
                    fd=new formData();
                    fd.name=itemname;
                    nameflag=true;
                    filename=getFileName(line);
                    if(filename!=null&&filename!=""){
                        fd.value=filename;
                        fileflag=true;
                    }else{
                        fileflag=false;
                    }
                    skipline=0;
                    continue;
                }
                continue;
            }
            if(nameflag&&!fileflag){
                if(skipline<1){
                    skipline++;
                    continue;
                }
                else{
                    if(line.indexOf(boundary)>=0){
                        nameflag=false;
                        fd.value=trim(sb.toString());
                        formdatas.addElement(fd);
                        sb=new StringBuffer("");
                    }else{
                        sb.append(line);
                    }
                }
                continue;
            }
            if(nameflag&&fileflag){
                if(skipline<1){
                    if(line.indexOf("Content-Type:")>=0){
                        fd.contentType=trim(line.substring(14));
                    }
                    else{
                        skipline++;
                    }
                    continue;
                }
                else{
                    if(line.indexOf(boundary)>=0){
                        if(bufferLength>=2){
                            bufferLength-=2;
                            temp=new byte[bufferLength];
                            for(i=0;i<bufferLength;i++)
                                temp[i]=buffer[i];
                            fd.file=temp;
                            buffer=new byte[size];
                            bufferLength=0;
                        }

                        formdatas.addElement(fd);
                        nameflag=false;
                        fileflag=false;
                    }
                    else{
                        for (i=0;i<ai[0];i++,bufferLength++)
                            buffer[bufferLength]=Linebyte[i];
                    }
                }
            }
        }
        return formdatas;
    }

    public String getName(String s){
        int i=s.indexOf(" name=\"");
        if(i>0){
            s=s.substring(i+7);
            i=s.indexOf("\"");
            return s.substring(0,i);
        }
        else {
            return "";
        }
    }

    public String getFileName(String s){
        try{
            int i=s.indexOf("filename=");
            if(i>=0){
                s=s.substring(i+10);
                if((i=s.indexOf("\""))>0)
                    s=s.substring(0,i);
                i=s.lastIndexOf("\\");
                if(i<0||i>=s.length()-1){
                    i=s.lastIndexOf("/");
                    if(i<0||i>=s.length()-1)
                        return s;
                }
                return s.substring(i+1);
            }else {
                return "";
            }
        }catch (Exception e){
            return "";
        }
    }

    private String readLine(byte Linebyte[],int ai[],
                            ServletInputStream servletinputstream,String CharacterEncoding){
        try{
            ai[0]= servletinputstream.readLine(Linebyte,0, Linebyte.length);
            if(ai[0]==-1){
                return null;
            }
        }catch (IOException ex){
            return null;
        }
        try{
            if(CharacterEncoding==null){
                return new String (Linebyte,0,ai[0]);
            }else{
                return new String (Linebyte,0,ai[0],CharacterEncoding);
            }
        }catch (Exception ex){
            return null;
        }
    }

    public String trim(String s){
        if(s.charAt(s.length()-1)=='\n'){
            if(s.length()<=2)
                return "";
            else
                s=s.substring(0,s.length()-2);
            return trim(s);
        }
        if(s.indexOf("\r\n")==0){
            s=s.substring(2);
            return trim(s);
        }
        return s;
    }
}

