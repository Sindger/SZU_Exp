import collections
import sys
import os

def getinfo(path):
    file_num=0
    code_lines=0
    space_lines=0
    comments_lines=0
    if not os.path.exists(path):
        print("路径错误")
        return
    if os.path.isdir(path):
        for i in os.listdir(path):
            if i.endswith(".py"):
                file_num+=1
                for code in open(path+'/'+i,encoding='utf-8'):
                    code_lines+=1
                    if code.startswith("#"):
                        comments_lines+=1
                    if code=="\n":
                        space_lines+=1
    elif os.path.isfile(path) and path.endswith(".py"):
        file_num+=1
        for i in open(path,encoding='utf-8'):
            code_lines+=1
            if i.startswith("#"):
                comments_lines+=1
            if i=="\n":
                space_lines+=1
    print(file_num,code_lines,space_lines,comments_lines)

if __name__=="__main__":
    getinfo('C:\\Users\\Sindger\\Desktop\\代码\\实验\\统计关键字.py')