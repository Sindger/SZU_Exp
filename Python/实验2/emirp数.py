def isPrime(number):
    if number<=1:
        return False
    for i in range(2,number-1):
        if number%i==0:
            return False
    return True

def reverse(number):
    n=0
    while number>0:
        n*=10
        n+=number%10;
        number//=10
    return n

def emirp(n):
    file=open("First"+str(n)+"_Emirp_Numbers","w")
    cnt=0
    i=0
    while cnt<n:
        i+=1
        if isPrime(i) and isPrime(reverse(i)) and i!=reverse(i):
            cnt+=1
            file.write(str(i)+" ")
            if cnt%10==0:
                file.write("\n")

n=eval(input())
emirp(n)