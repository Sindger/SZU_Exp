def displayempty(num):
    empty='        '
    for i in range(0, num):
        print(empty, end="    ")
    print("")

def displaylineA(num):
    lineA = '    {o,o}'
    for i in range(0,num):
        print(lineA,end="    ")
    print("")

def displaylineB(num):
    lineB = '    /)_) '
    for i in range(0, num):
        print(lineB, end="    ")
    print("")

def displaylineC(num):
    lineC='     " " '
    for i in range(0, num):
        print(lineC, end="    ")
    print("")

if __name__=="__main__":
    n = int(input())
    displayempty(n)
    displaylineA(n)
    displaylineB(n)
    displaylineC(n)