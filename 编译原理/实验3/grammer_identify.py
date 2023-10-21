#-*- coding: utf-8 -*-

import re
from typing import List
class production:
    def __init__(self, l: str, r: str):
        self.left = l
        self.right = r

class Grammer:
    def __init__(self):
        self.V = []   # 变量
        self.T = []   # 终结符
        self.P = []   # 产生式
        self.S = []   # 开始符
        self.separator = ','  # 分隔符号
        self.arrow = '->'  # 箭头
        self.sentences = [""] * 20  # 保存产生式的临时变量
        self.row = 0  # 文件行数

    # 分割变量、终结符、开始符号
    def split(self, s: str, sv: List[str], flag: str = ','):
        for c in s.split(flag): # 以逗号分割
            sv.append(c.strip()) # 去除空格

    def split_grammar(self, s: str, ss: List[production], flag: str = ' ', separator: str = '->'): # 分割产生式
        for v in s.split(flag):
            l, r = re.split(separator, v)
            ss.append(production(l.strip(), r.strip()))

    #对变量进行初始化
    def init(self):
        for i in range(self.row):
            if i == 0:
                self.split(self.sentences[i], self.V, self.separator) # 分割变量
            elif i == 1:
                self.split(self.sentences[i], self.T, self.separator) # 分割终结符
            elif i == self.row - 1:
                self.split(self.sentences[i], self.S, self.separator) # 分割开始符号
            else:
                self.split_grammar(self.sentences[i], self.P, self.separator, self.arrow) # 分割产生式

    # 检查四元组语法
    def check_grammar_legal(self):
        islegal = True

        # 检查变量格式
        for c in self.V:
            if not ('A' <= c <= 'Z'):
                islegal = False  # 不合法
                print("变量V的格式不合法:所有变量必须使用大写字母")
                break

        # 检查终结符格式
        for c in self.T:
            if c in self.V:  # 终结符与变量有交集
                islegal = False
                print("终结符T的格式不合法:必须满足V∩T=空集")
                break

        # 检查起始符号
        for c in self.S:
            if c not in self.V:  # 不为变量，不合法
                islegal = False
                print("起始符号S的格式不合法:必须满足S∈V")
                break

        # 检查产生式格式
        for i in range(len(self.P)):
            # 左部的长度必须大于0
            if not (len(self.P[i].left) > 0): # 左部长度不为0
                islegal = False
                print("产生式P的不合法：{}{}{}必须满足左部α∈(V∪T)+".format(self.P[i].left, self.arrow, self.P[i].right))
                break
            # 左部的每个字符必须在V∪T中
            hasV = False
            # 检查左部
            for j in range(len(self.P[i].left)):
                isVorT = False
                for k in range(len(self.V)):
                    if self.P[i].left[j] == self.V[k]:  # 为变量
                        hasV = True
                        isVorT = True
                        break
                if not isVorT:  # 是否含有V或者T
                    for k in range(len(self.T)):
                        if self.P[i].left[j] == self.T[k]:  # 为终结符
                            isVorT = True
                            break
                if not isVorT:  # 不为终结符或变量
                    islegal = False
                    print("产生式P的不合法：{}{}{}不满足左部α∈(V∪T)+".format(self.P[i].left, self.arrow, self.P[i].right))
                    break
            if not hasV:
                islegal = False
                print("产生式P的不合法：{}{}{}不满足左部α中至少有V中的一个元素出现".format(self.P[i].left, self.arrow, self.P[i].right))
                break

            # 检查右部
            for j in range(len(self.P[i].right)):
                isVorT = False
                for k in range(len(self.V)):
                    if self.P[i].right[j] == self.V[k]:
                        isVorT = True
                        break
                if not isVorT:
                    for k in range(len(self.T)):
                        if self.P[i].right[j] == self.T[k]:
                            isVorT = True
                            break
                if not isVorT:
                    islegal = False
                    print("产生式P的格式不合法：{}{}{}不满足右部β∈(V∪T)+".format(self.P[i].left, self.arrow, self.P[i].right))
                    break
                if not islegal:
                    break
        return islegal

    def isType1(self):
        isType1 = True
        for i in range(len(self.P)): # 检查是否为1型文法
            if len(self.P[i].left) > len(self.P[i].right):
                isType1 = False
                print("G不属于1型文法，因为", self.P[i].left, self.arrow, self.P[i].right, "不满足条件|β|≥|α|")
                break
        return isType1

    def isType2(self):
        isType2 = True
        for i in range(len(self.P)): # 检查是否为2型文法
            inV = False
            if len(self.P[i].left) > len(self.P[i].right):
                isType2 = False
                print("G不属于2型文法，因为", self.P[i].left, self.arrow, self.P[i].right, "不满足条件|β|≥|α|")
                break
            if len(self.P[i].left) == 1:
                for j in range(len(self.V)):
                    if self.P[i].left[0] == self.V[j]:
                        inV = True
                        break
            else:
                isType2 = False
                print("G不属于2型文法，因为", self.P[i].left, self.arrow, self.P[i].right, "不满足条件α∈V")
                break
            if not inV:
                isType2 = False
                print("G不属于2型文法，因为", self.P[i].left, self.arrow, self.P[i].right, "不满足条件α∈V")
                break
        return isType2

    def isType3(self):
        isType3 = True
        for i in range(len(self.P)):
            # 判断产生式左部是否在变量集
            if len(self.P[i].left) == 1:  # 长度为1
                inV = False
                for j in range(len(self.V)):
                    if self.P[i].left[0] == self.V[j]:
                        inV = True
                        break
                if not inV:  # 不在变量集中
                    isType3 = False
                    break
            else:
                isType3 = False  # 长度不为1
                break
        if not isType3:
            print("G不属于3型文法，因为", self.P[i].left, self.arrow, self.P[i].right, "不满足条件A∈V")
            return isType3

        # 判断产生式右部是否符合w或者wB
        for i in range(len(self.P)):
            for j in range(len(self.P[i].right)):
                inT = False
                for k in range(len(self.T)):
                    if self.P[i].right[j] == self.T[k]:
                        inT = True
                        break
                if not inT:  # 若不属于终结符集合
                    if j == 0:
                        isType3 = False
                        break
                    if j != len(self.P[i].right) - 1:
                        isType3 = False
                        break
                    inV = False
                    for k in range(len(self.V)):
                        if self.P[i].right[j] == self.V[k]:
                            inV = True
                            break
                    if not inV:
                        isType3 = False
                    if not isType3:
                        break
            if not isType3:
                break

        if not isType3: # 不满足条件
            print("G不属于3型文法，因为", self.P[i].left, self.arrow, self.P[i].right, "不满足条件A->w或者A->wB")
        return isType3

    def getGrammerType(self):
        if self.check_grammar_legal():
            if self.isType3():
                print("G属于3型文法")
            else:
                if self.isType2():
                    print("G属于2型文法")
                else:
                    if self.isType1():
                        print("G属于1型文法")
                    else:
                        print("G为0型文法")
        else:
            print("G不是文法")

    def read_file(self,file_name):
        with open(file_name, 'r') as f:
            self.row=0
            for lint in f:
                if self.row<20:
                    self.sentences[self.row]=lint.rstrip()
                    self.row+=1
                else:
                    print("文件打开失败")
                    break
        self.init()

    def Print_Sentence(self):
        for i in range(self.row):
            print(self.sentences[i])

    def Print_trtrad(self):
        print("G = {{", end="")
        for i in range(len(self.V)):
            if i ==len(self.V) - 1:
                print(self.V[i], end="")
            else:
                print(self.V[i], end=",")
        print("},{", end="")
        for i in range(len(self.T)):
            if i == len(self.T) - 1:
                print(self.T[i], end="")
            else:
                print(self.T[i], end=",")
        print("},{", end="")
        for i in range(len(self.P)):
            if i == len(self.P) - 1:
                print(self.P[i].left+self.arrow+self.P[i].right, end="")
            else:
                print(self.P[i].left+self.arrow+self.P[i].right, end=",")
        print("},{", end="")
        for i in range(len(self.S)):
            if i == len(self.S) - 1:
                print(self.S[i], end="")
            else:
                print(self.S[i], end=",")
        print("}}")

    def get_production(self):
        production=[]
        for i in range(len(self.P)):
            production.append(self.P[i].left+self.arrow+self.P[i].right)
        return production

def identify(file_name):
    g=Grammer()
    g.read_file(file_name)
    production=g.get_production()
    return production

if __name__ == '__main__':
    g = Grammer()
    file_name = input("请输入文件名：")
    file_name = file_name + ".txt"
    g.read_file(file_name)
    g.Print_Sentence()
    g.Print_trtrad()
    g.getGrammerType()