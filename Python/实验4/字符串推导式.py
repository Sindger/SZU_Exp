def CharacterUpper():
    list = input("Please input the list:")
    list = list.split()
    l = []
    l = [i[0].upper() for i in list]
    print(l)

def OddWord():
    list = input("Please input the list:")
    list = list.split()
    l = []
    l = [list[i] for i in range(0,len(list)+1,2)]
    print(l)

def SelectWord():
    list = input("Please input the list:")
    list = list.split()
    l = []
    l = [i[3:len(i)] for i in list if i[:2]=="TA"]
    print(l)

def LenList():
    list = input("Please input the list:")
    list = list.split()
    l = []
    l = [(i,len(i)) for i in list]
    print(l)

def LenDic():
    list = input("Please input the list:")
    list = list.split()
    l = {}
    l = {i:len(i) for i in list}
    print(l)

if __name__=="__main__":
    num=eval(input("Please input a number to select a mode:"))
    if num==1:
        CharacterUpper()
    elif num==2:
        OddWord()
    elif num==3:
        SelectWord()
    elif num==4:
        LenList()
    else:
        LenDic()