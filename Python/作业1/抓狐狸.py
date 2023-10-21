import random

cave=[0,0,0,0,0]
num=random.randint(0,4)
cave[num]=1

def move(cave):
    rand=[-1,1]
    flag=0
    for i in range(0,5):
        if cave[i]==1:
            flag=i
    if flag==4:
        cave[flag]=0
        cave[flag-1]=1
    elif flag==0:
        cave[flag]=0
        cave[flag+1]=1
    else:
        number=random.randint(0,1)
        cave[flag+rand[number]]=0

if __name__=="__main__":
    cnt=0
    while 1:
        cavenum=int(input("这里有5个洞口，请选择小狐狸所在的洞口:"))
        cnt+=1
        if cave[cavenum-1]==1:
            print("恭喜你在第%d天的第%d个洞口抓住了狐狸"%(cnt,cavenum))
            break
        else:
            print("很遗憾，该洞口内没有狐狸")
            move(cave)