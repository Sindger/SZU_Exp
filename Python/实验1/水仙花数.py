n=int(input())
for i in range(pow(10,n-1),pow(10,n)):
    Sum=i
    Num=0
    while Sum>0:
        Num+=pow(Sum%10,n)
        Sum//=10
    if Num==i:
        print(i)