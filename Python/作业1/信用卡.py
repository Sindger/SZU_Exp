def validCredit(cardNum):
    reverse=[int(i) for i in reversed(cardNum)]
    line=[i*2 for i in reverse[1::2]]
    line=[i//10+i%10 for i in line]
    Sum1=sum(line)
    Sum2=sum(reverse[::2])
    Sum3=Sum1+Sum2
    if Sum3%10==0:
        return True
    else:
        return False

if __name__=="__main__":
    cardNum=input("请输入信用卡号码:")
    if(validCredit(cardNum)):
        Num=cardNum[0]+cardNum[1]
        Num=int(Num)
        if Num==34 or Num==37:
            print("Valid,American Express")
        elif Num>=51 and Num<=55:
            print("Valid,MasterCard")
        else:
            print("Valid,Visa")
    else:
        print("Invalid")