arr1=input('')
num1=[int(n) for n in arr1.split()]
arr2=input('')
num2=[int(n) for n in arr2.split()]
sum=0
if len(num1)!=len(num2):
    print(-1)
else:
    for i in range(0,len(num1)):
        sum+=num1[i]*num2[i]
    print(sum)