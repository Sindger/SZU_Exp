def match_pattern(list1,list2):
    arr=iter(list1)
    return all(i in arr for i in list2)

if __name__ == "__main__":
    list1=input("请输入列表1的元素：").split()
    list2=input("请输入列表2的元素：").split()
    print(list1)
    print(list2)
    print(match_pattern(list1,list2))