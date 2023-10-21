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
    for file in os.listdir(path):
        for i in os.listdir(path+'/'+file):
            if i.endswith(".py"):
                file_num+=1
                for code in open(path+'/'+file+'/'+i,encoding='utf-8'):
                    code_lines+=1
                    if code.startswith("#"):
                        comments_lines+=1
                    if code=="\n":
                        space_lines+=1
    print(file_num,code_lines,space_lines,comments_lines)

if __name__=="__main__":
    getinfo('C:\\Users\\Sindger\\Desktop\\代码')