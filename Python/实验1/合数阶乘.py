n=int(input())
for i in range(n,3,-1):
    if i%2==0 or i%3==0 or i%5==0:
        Num=1
        for j in range(1,i+1):
            Num*=j
        print(i,"!:",Num)
