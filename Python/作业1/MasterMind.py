def checklen(str):
    if len(str)!=5:
        return False
    for i in range(1,5):
        for j in range(0,i):
            if str[i]==str[j]:
                return False
    return True

def checknum(str1,str2):
    cnt=0
    len1=len(str1)
    len2=len(str2)
    for i in range(len1):
        for j in range(len2):
            if str2[j]==str1[i]:
                cnt+=1
    return cnt

def checkloc(str1,str2):
    cnt=0
    len1 = len(str1)
    for i in range(len1):
        if str1[i]==str2[i]:
            cnt+=1
    return cnt

if __name__=="__main__":
    num=0
    while 1:
        num=input("Please input a five-digit num:")
        if checklen(num):
            break
        else:
            print("Error,Please re-enter")
    cnt=0
    print("You can input a num to guess the correact num or input out to exit")
    while cnt<10:
        cnt+=1
        if cnt!=10:
            sum=input("Please input a num that you want:")
        if sum == "out":
            print("You've failed,the number of times you guess is %d" %(cnt-1))
            break
        elif checklen(sum)==False:
            print("Numbers are not legitimate")
        elif sum!=num:
            number=checknum(num,sum)
            loc=checkloc(num,sum)
            print("Num incorrect")
            print("But you guessed %d numbers correctly"%number)
            print("And you guessed the position of %d numbers correctly"%loc)
            print("Please input another num you want:")
        else:
            print("You've won,the number of times you guess is %d"%cnt)
            break
    if cnt==10:
        print("Game over,you've guess it more than 10 times")