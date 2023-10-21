def merge_sort(lis1,list2):
    arr=list1+list2
    arr.sort()
    return arr

def merge_unsort(list1,list2):
    i=0
    j=0
    arr=[]
    while i<len(list1) and j<len(list2):
        if list1[i]<list2[j]:
            arr.append(list1[i])
            i+=1
        else:
            arr.append(list2[j])
            j+=1
    if i<len(list1):
        arr.append(list1[i])
        i+=1
    if j<len(list2):
        arr.append(list2[j])
        j+=1
    return arr

if __name__ == "__main__":
    list1=input("请输入列表1的元素：").split()
    list2=input("请输入列表2的元素：").split()
    arr=merge_sort(list1,list2)
    arr=merge_unsort(list1,list2)
    print(arr)