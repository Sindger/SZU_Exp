import os
import sys

def isAlpha(ch):
    return (ch>='a' and ch<='z') or (ch>='A' and ch<='Z')

def isNum(ch):
    return ch>='0' and ch<='9'

def isAlphaNum(ch):
    return isAlpha(ch) or isNum(ch)

def isSpace(ch):
    return ch==' ' or ch=='\t' or ch=='\r' or ch=='\n'

def isKeyWord(s):
    return s in ['include','define','pragma','using','namespace','if','else','bool','int','char','float','double']

#读取文件中的每一个单词
def readWord(f):
    str=''
    ch=f.read(1)
    while ch!=EOFError and (isAlpha(ch) or ch=='_'):
        str+=ch
        ch=f.read(1)
    return str

def getstr(f):
    str=''
    ch=f.read(1)
    while ch!=EOFError and ch!='\"':
        str+=ch
        ch=f.read(1)
    return str

def getnum(f):
    str=''
    ch=f.read(1)
    while ch!=EOFError and isNum(ch):
        str+=ch
        ch=f.read(1)
    return str

def getchar(f):
    str=''
    ch=f.read(1)
    while ch!=EOFError and ch!='\'':
        str+=ch
        ch=f.read(1)
    return str

def output(f,type,value):
    f.write("("+type+":"+value+")"+'\r')

if __name__=="__main__":
    fp=open('a.txt','r')
    if fp==None:
        print("文件打开失败")
        sys.exit()
    with open('b.txt','a') as f:
        print("文件打开成功,开始扫描目标文件")
        ch=fp.read(1)
        str=''
        while ch!=EOFError:
            if ch==' ' or ch=='\n' or ch=='\r' or '':
                ch=fp.read(1)
                continue
            if isAlpha(ch):
                str+=ch
                str+=readWord(fp)
                if isKeyWord(str):
                    output(f,'关键字',str)
                else:
                    output(f,'标识符',str)
                str=''
            elif isNum(ch):
                str+=ch
                str+=getnum(fp)
                output(f,'数字',str)
                str=''
            elif ch=='#':
                str+=readWord(fp)
                output(f,'关键字',str)
                str=''
            elif ch in ['[',']','<','>','+','-','*','/','=','!','&','|','(',')']:
                output(f,'运算符',ch)
            elif ch in [',','{','}',';','，',"'",'"']:
                output(f,'标点符号',ch)
            elif ch=='\"' or ch=='\'':
                if ch=='\'':
                    str+=getchar(fp)
                    output(f,'字符',str)
                    str=''
                else:
                    str+=getstr(fp)
                    output(f,'字符串',str)
                    str=''
            else:
                ch=fp.read(1)
                continue
            ch=fp.read(1)
    fp.close()
    print("扫描结束")