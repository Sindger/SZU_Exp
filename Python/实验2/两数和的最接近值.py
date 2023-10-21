def twoSumCloest(*num,target):
    length=len(num)
    min=100000
    for i in range(1,length):
        for j in range(0,i):
            number=num[i]+num[j]
            if abs(target-number)<min:
                min=target-number
    print(min)

nums=input("")
num=[int(n) for n in nums.split()]
target=int(input())
twoSumCloest(*num,target=target)