import math
num=int(input())
severnum=0
flag=0
if num<0:
    severnum = -severnum
    while num>0:
        number=num%7
        severnum+=number*pow(10,flag)
        flag+=1
        num//=7
    severnum=-severnum
else:
    while num>0:
        number = num % 7
        severnum += number * pow(10, flag)
        flag += 1
        num //= 7
print(severnum)