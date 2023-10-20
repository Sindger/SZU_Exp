import os
import sys
import docx
import re

#判断字符是否为数字
def is_digit(c):
    return c>='0' and c<='9'

#判断字符是否为小数点
def is_dot(c):
    return c=='.'

#判断字符是否为字母E
def is_E(c):
    return c=='E' or c=='e'

#判断字符是否为正负号
def is_sign(c):
    return c=='+' or c=='-'

#获取当前状态
def get_current_state(c):
    if(is_digit(c)):
        return 'digit'
    elif(is_dot(c)):
        return 'dot'
    elif(is_sign(c)):
        return 'plus_minus'
    elif(is_E(c)):
        return 'E'
    else:
        return 'other'

#获取下一个状态
def get_state(initial,receive):
    translation={
        'start':{
            'digit':'state1',
            'plus_minus':'plus_minus_end',
            'E':'E_end',
            'dot':'state3',
            'other':'other',
        },
        'state1':{
            'digit':'state1',
            'dot':'state2',
            'E':'state4',
            'plus_minus': 'legitimate_end',
            'other':'legitimate_end',
        },
        'state2':{
            'digit':'state2',
            'E':'state4',
            'plus_minus':'legitimate_end',
            'dot':'legitimate_end',
            'other':'legitimate_end',
        },
        'state3':{
            'digit':'state2',
            'plus_minus':'illegal_end',
            'E':'illegal_end',
            'dot':'illegal_end',
            'other':'illegal_end',
        },
        'state4':{
            'digit':'state6',
            'plus_minus':'state5',
            'E': 'illegal_end',
            'dot': 'illegal_end',
            'other':'illegal_end',
        },
        'state5':{
            'digit':'state6',
            'plus_minus':'illegal_end',
            'E': 'illegal_end',
            'dot': 'illegal_end',
            'other':'illegal_end',
        },
        'state6':{
            'digit':'state6',
            'dot':'legitimate_end',
            'plus_minus': 'legitimate_end',
            'E': 'legitimate_end',
            'other':'legitimate_end',
        },
        'other':{
            'other':'other',
            'dot':'end',
            'E':'other',
            'plus_minus':'other',
            'digit':'end',
        },
    }
    return translation.get(initial).get(receive)


def get_digit(s):
    current_state='start'
    receive_state=''
    tokens=[]
    buffer=''
    for i in range(len(s)):
        receive_state=get_current_state(s[i])
        next_state=get_state(current_state,receive_state)
        if next_state=='state1':
            buffer+=s[i]
            current_state=next_state
        elif next_state=='state2':
            buffer+=s[i]
            current_state=next_state
        elif next_state=='state3':
            buffer+=s[i]
            current_state=next_state
        elif next_state=='state4':
            buffer+=s[i]
            current_state=next_state
        elif next_state=='state5':
            buffer+=s[i]
            current_state=next_state
        elif next_state=='state6':
            buffer+=s[i]
            current_state=next_state
        elif next_state == 'other':
            buffer+=s[i]
            current_state = next_state
        elif next_state=='legitimate_end':
            tokens.append('(数字,'+buffer+')')
            buffer=''
            buffer+=s[i]
            current_state='start'
        elif next_state=='illegal_end':
            buffer+=s[i]
            tokens.append('(异常,'+buffer+')')
            buffer=''
            buffer+=s[i]
            current_state='start'
        elif next_state=='end':
            tokens.append('(其他,'+buffer+')')
            buffer=''
            buffer+=s[i]
            current_state='state1'
        elif next_state=='plus_minus_end':
            if buffer!='':
                tokens.append('(其他,'+buffer+')')
            tokens.append('(其他,'+s[i]+')')
            buffer=''
            current_state='start'
        elif next_state=='E_end':
            if buffer != '':
                tokens.append('(其他,' + buffer + ')')
            tokens.append('(其他,'+s[i]+')')
            buffer=''
            current_state='start'
    if buffer!='':
        if current_state in {'state1','state2','state6'}:
            tokens.append('(数字,'+buffer+')')
        elif current_state in {'state3','state4','state5'}:
            tokens.append('(异常,'+buffer+')')
        else:
            tokens.append('(其他,'+buffer+')')
    return tokens

#判断字母是否为无符号数
def is_unsigned_integer(s):
    #创建文本文件存储结果
    f=open('result.txt','w')
    enter=0
    for i in s:
        if(any(is_digit(c) for c in i)):
            tokens=get_digit(i)
            for j in tokens:
                f.write(j)
                enter+=1
                if(enter%5==0):
                    f.write('\n')
        else:
            str="(其他，"+i+")"
            f.write(str)
            enter+=1
            if(enter%5==0):
                f.write('\n')
    f.close()

if __name__=="__main__":
    str=""
    doc=docx.Document('question.docx')
    for para in doc.paragraphs:
        s=para.text
        str+=s
    s=str.split(" ")
    #剔除列表中的空串
    while '' in s:
        s.remove('')
    is_unsigned_integer(s)