def cookies(list1,list2):
    i=0
    j=0
    num=0
    while i<len(list1) and j<len(list2):
        if list1[i]>list2[j]:
            j+=1
        else:
            i+=1
            j+=1
            num+=1
    return num

if __name__ == "__main__":
    list1=input("请输入贪吃指数：").split()
    list2=input("请输入饼干尺寸：").split()
    list1.sort()
    list2.sort()
    num=cookies(list1,list2)
    print(num)