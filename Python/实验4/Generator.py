def generate_triangle():
    a=1
    n=1
    while 1:
        yield a
        a+=n+1
        n+=1

def generate_triangle_under(n):
    line=[]
    it=generate_triangle()
    for i in range(n):
        flag=next(it)
        if flag!=None:
            line.append(flag)
    return line

if __name__=="__main__":
    n=eval(input("Please input a number:"))
    print(generate_triangle_under(n))