#-*- coding: utf-8 -*-
import os
import sys

class Suffix:
    def __init__(self,expression):
        self.Expression=expression


class Grammar_Guidance:
    def __init__(self,Analysis_text):
        self.Analysis_text=Analysis_text
        self.Expression_List=[] #表达式列表
        self.Suffix_List=[] #后缀表达式列表
        self.Analysis_Result=[] #分析结果
        self.Analysis_index=1 #分析索引
        self.Expression_Split()

    def Expression_Split(self):
        self.Analysis_text=self.Analysis_text.replace(" ","")
        self.Expression_List=self.Analysis_text.split(";")
        return self.Expression_List

    def Get_Suffix(self): #获取后缀表达式
        for i in self.Expression_List:
            suffix=self.Infix_to_Suffix(i)
            self.Suffix_List.append(suffix) #将后缀表达式添加到后缀表达式列表中
        for i in self.Suffix_List:
            print(i.Expression)

    def Infix_to_Suffix(self,expression):
        Operator=['+','-','*','/','&','|','!','=','(']
        Operator_Stack=[]
        Suffix_Stack=[]
        buffer=""
        for i in expression:
            if i in Operator:
                if buffer!="":
                    Suffix_Stack.append(buffer)
                    buffer=""
                Operator_Stack.append(i)
            elif i==")":
                if buffer!="":
                    Suffix_Stack.append(buffer)
                    buffer=""
                while Operator_Stack[-1]!="(":
                    Suffix_Stack.append(Operator_Stack.pop())
                Operator_Stack.pop()
            else:
                buffer+=i
        if buffer!="":
            Suffix_Stack.append(buffer)
        while Operator_Stack:
            Suffix_Stack.append(Operator_Stack.pop())
        suffix=Suffix(Suffix_Stack)
        return suffix

    def Get_Result(self):
        Operator = ['+', '-', '*', '/', '&', '|', '!', '=']
        for i in self.Suffix_List:
            operand_stack=[]
            for j in i.Expression:
                if j not in Operator:
                    operand_stack.append(j)
                else:
                    if j!="=":
                        operand1=operand_stack.pop()
                        operand2=operand_stack.pop()
                        result=operand2+j+operand1
                        result_index="t"+str(self.Analysis_index)
                        self.Analysis_index+=1
                        self.Analysis_Result.append(result_index+"="+result)
                        operand_stack.append(result_index)
                    else:
                        operand1 = operand_stack.pop()
                        operand2 = operand_stack.pop()
                        result = operand2 + j + operand1
                        self.Analysis_Result.append(result)

    def Print_Result(self):
        #创建一个result文件
        file=open("result.txt","w")
        for i in self.Analysis_Result:
            file.write(i+"\n")
            print(i)
        file.close()

if __name__ == "__main__":
    #打开文件“Analysis.txt”
    file=open("Analysis.txt","r")
    Analysis_text=file.read() #读取文件内容
    file.close()
    analyse=Grammar_Guidance(Analysis_text) #创建一个类对象
    analyse.Get_Suffix() #获取后缀表达式
    analyse.Get_Result() #获取分析结果
    analyse.Print_Result() #打印分析结果
