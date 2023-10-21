def Analyse():
    txta="hyde.txt"
    txtb="treasure.txt"
    f1=open(txta,'a+',encoding="utf-8")
    with open(txtb,'r',encoding="utf-8") as f2:
        f1.write('\n')
        for i in f2:
            f1.write(i)
    f=open(txta,'r',encoding="utf-8")
    txt1=f.read()
    f.close()
    f1.close()
    for i in ' ,.\n" ':
        txt1 = txt1.replace(i,' ')
    list=txt1.split()
    cnt=dict()
    for i in list:
        cnt[i]=cnt.get(i,0)+1
    sort=sorted(cnt.items(),key=lambda item:item[1],reverse=True)
    print("Robert Louis Stevenson:")
    for i in range(20):
        if i%2==1:
            print(sort[i])
        else:
            print(sort[i],end=" ")
    txt="war.txt"
    f = open(txt, 'r', encoding="utf-8")
    txt1 = f.read()
    f.close()
    f1.close()
    for i in ' ,.\n" ':
        txt1 = txt1.replace(i, ' ')
    list = txt1.split()
    cnt = dict()
    for i in list:
        cnt[i] = cnt.get(i, 0) + 1
    sort = sorted(cnt.items(), key=lambda item: item[1], reverse=True)
    print("Leo Tolstoy:")
    for i in range(20):
        if i % 2 == 1:
            print(sort[i])
        else:
            print(sort[i], end=" ")
if __name__=="__main__":
    Analyse()