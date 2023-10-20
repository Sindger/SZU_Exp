import os
import sys
import docx
import re

#�ж��ַ��Ƿ�Ϊ����
def is_digit(c):
    return c>='0' and c<='9'

#�ж��ַ��Ƿ�ΪС����
def is_dot(c):
    return c=='.'

#�ж��ַ��Ƿ�Ϊ��ĸE
def is_E(c):
    return c=='E' or c=='e'

#�ж��ַ��Ƿ�Ϊ������
def is_sign(c):
    return c=='+' or c=='-'

#��ȡ��ǰ״̬
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

#�Ƿ�Ϊ����״̬
def get_encryption_state(c):
    return c in 'ABCDOFGHIJKLMN'

#����ӳ���
def get_map(c):
    map={
        'A':'0',
        'B':'1',
        'C':'2',
        'D':'3',
        'O':'4',
        'F':'5',
        'G':'6',
        'H':'7',
        'I':'8',
        'J':'9',
        'K':'.',
        'L':'E',
        'M':'+',
        'N':'-',
    }
    return map.get(c)

#��ȡ��һ��״̬
def get_state(initial,receive):
    transition={
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
    return transition.get(initial).get(receive)


def get_digit(s):
    current_state='start'
    receive_state=''
    tokens=[]
    buffer=''
    for i in range(len(s)):
        ch=s[i]
        if ch in 'ABCDOFGHIJKLMN':
            ch=get_map(ch)
        receive_state=get_current_state(ch)
        next_state=get_state(current_state,receive_state)
        if next_state=='state1':
            buffer+=ch
            current_state=next_state
        elif next_state=='state2':
            buffer+=ch
            current_state=next_state
        elif next_state=='state3':
            buffer+=ch
            current_state=next_state
        elif next_state=='state4':
            buffer+=ch
            current_state=next_state
        elif next_state=='state5':
            buffer+=ch
            current_state=next_state
        elif next_state=='state6':
            buffer+=ch
            current_state=next_state
        elif next_state == 'other':
            buffer+=ch
            current_state = next_state
        elif next_state=='legitimate_end':
            tokens.append('(����,'+buffer+')')
            buffer=''
            buffer+=ch
            current_state='start'
        elif next_state=='illegal_end':
            # buffer+=ch
            # tokens.append('(�쳣,'+buffer+')')
            buffer=''
            buffer+=ch
            current_state='start'
        elif next_state=='end':
            # tokens.append('(����,'+buffer+')')
            buffer=''
            buffer+=ch
            current_state='state1'
        elif next_state=='plus_minus_end':
            # if buffer!='':
            #     tokens.append('(����,'+buffer+')')
            # tokens.append('(����,'+ch+')')
            buffer=''
            current_state='start'
        elif next_state=='E_end':
            # if buffer != '':
            #     tokens.append('(����,' + buffer + ')')
            # tokens.append('(����,'+ch+')')
            buffer=''
            current_state='start'
    if buffer!='':
        if current_state in {'state1','state2','state6'}:
            tokens.append('(����,'+buffer+')')
        # elif current_state in {'state3','state4','state5'}:
        #     tokens.append('(�쳣,'+buffer+')')
        # else:
        #     tokens.append('(����,'+buffer+')')
    return tokens

#�ж��Ƿ�Ϊ�޷�����
def is_unsigned_integer(s):
    #�����ı��ļ��洢���
    f=open('result1-2.txt','w')
    enter=0
    for i in s:
        if(any(get_encryption_state(c) for c in i)):
            tokens=get_digit(i)
            for j in tokens:
                f.write(j)
                enter+=1
                if(enter%5==0):
                    f.write('\n')
        # else:
        #     str="(������"+i+")"
        #     f.write(str)
        #     enter+=1
        #     if(enter%5==0):
        #         f.write('\n')
    f.close()

if __name__=="__main__":
    # str="BCD*abc+def/JJKC+JKJL+c"
    # is_unsigned_integer(str)
    str=''
    doc=docx.Document('encrypt.docx')
    for para in doc.paragraphs:
        s=para.text
        str+=s
    s=str.split(" ")
    #�޳��б��еĿմ�
    while '' in s:
        s.remove('')
    is_unsigned_integer(s)