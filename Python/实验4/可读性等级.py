def readability():
    txt=input("Please input a sentence:")
    txt1=txt
    for i in ' ,.!?" ':
        txt1=txt1.replace(i,' ')
    txt1=txt1.split()
    L=0
    sum=0
    for i in txt:
        if i=='.' or i=='?' or i=='!':
            sum+=1
        i = i.lower()
        if i >= 'a' and i <= 'z':
            L += 1
    L = (L) / len(txt1) * 100
    S=sum/len(txt1)*100
    index=0.0588*L-0.296*S-15.8
    index=round(index)
    if index<=1:
        print("Before Grade 1")
    elif index>=16:
        print("Grade 16+")
    else:
        print("Grand %d"%index)

if __name__=="__main__":
    readability()
