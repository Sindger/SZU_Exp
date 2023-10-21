import os
import random
cnt=0
#生成长度为2-8的单个单词
def create_word():
    str=''
    number=random.randint(2,8)
    for i in range(number):
        str+=chr(random.randint(97,122))
    return str

def create_word_txt(fp):
    word_list = []
    number = random.randint(80, 100)
    for i in range(number):
        word_list.append(create_word())
    for i in word_list:
        fp.write(i)
        fp.write(' ')

#生成单词列表
def create_word_list():
    word_list=[]
    number=random.randint(5,20)
    for i in range(number):
        word_list.append(create_word())
    return word_list

#生成单词列表的字符串
def create_word_list_str(fp,word_list):
    global cnt
    for i in word_list:
        cnt+=len(i)
        if cnt>=30000:
            break
        fp.write(i)
        fp.write(' ')
    fp.write('\r')

def create_txt():
    number=random.randint(20000,30000)
    fp=open('test.txt','w')
    for i in range(int(number)):
        word_list=create_word_list()
        create_word_list_str(fp,word_list)
    print('已生成带过滤文本')
    fp.close()

if __name__=='__main__':
    create_txt()
    with open('word_list.txt','a') as fp:
        create_word_txt(fp)
    word_list=[]
    with open('word_list.txt','r') as fp:
        word_list=fp.read().split(' ')
    word_list=word_list[:-1]
    passage=[]
    with open('test.txt','r') as fp:
        passage=fp.readlines()
    for i in range(len(passage)):
        passage[i]=passage[i].split(' ')
        passage[i]=passage[i][:-1]
    for i in range(len(passage)):
        for j in range(len(passage[i])):
            if passage[i][j] in word_list:
                passage[i][j]='*'*len(passage[i][j])
    with open('passage.txt','w') as fp:
        for i in passage:
            for j in i:
                fp.write(j)
                fp.write(' ')
            fp.write('\r')
    print('文本过滤完成')