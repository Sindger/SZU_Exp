def offByOne(str1,str2):
    if str1==str2 or len(str1)==0 or len(str2)==0 or len(str1)!=len(str2):
        return False
    cnt=0;
    length=len(str1)
    for i in range(length):
        if str1[i]!=str2[i]:
            cnt+=1
        if cnt>1:
            return False
    return True

def offBySwap(str1,str2):
    if str1==str2 or len(str1)==0  or len(str2)==0 or len(str1)!=len(str2):
        return False
    length=len(str1)
    cnt=0
    tmp=[]
    for i in range(length):
        if str1[i]!=str2[i]:
            cnt+=1
            tmp.append(i)
            if cnt>2:
                return False
    if cnt!=2:
        return False
    return str1[tmp[0]]==str2[tmp[1]] and str1[tmp[1]]==str2[tmp[0]]

def offByExtra(str1,str2):
    if str1 == str2 or len(str1) == 0 or len(str2) == 0 or abs(len(str1)-len(str2))>1:
        return False
    Index=-1
    if len(str1)>len(str2):
        str=str1
        str1=str2
        str2=str
    length=len(str1)
    for i in range(length):
        if str1[i]!=str2[i]:
            Index=i
            break
    if Index==-1:
        return True
    str2=str2[:Index]+str2[Index+1:]
    return str1==str2

if __name__=="__main__":
    txt="EnglishWords.txt"
    f=open(txt,'r',encoding="utf-8")
    t=f.read()
    f.close()
    list=t.split()
    word=input("Please input a word:")
    neighbors=[]
    for i in list:
        if offByOne(i,word) or offBySwap(i,word) or offByExtra(i,word):
            neighbors.append(i)
    print('%s has %d neighbor(s)' %(word,len(neighbors)))
    print(neighbors)