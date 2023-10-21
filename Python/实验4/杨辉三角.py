def Yanghui_triangle(num):
    triangle=[[1]]
    for i in range(2,num+1):
        triangle.append([1]*i)
        for j in range(1,i-1):
            triangle[i-1][j]=triangle[i-2][j]+triangle[i-2][j-1]
    width=len(str(triangle[-1][len(triangle[-1])//2]))+3
    col=len(triangle[-1])*width
    for i in triangle:
        line=[]
        for j in i:
            line.append('{0:^{1}}'.format(str(j),width))
        print('{0:^{1}}'.format(''.join(line),col))

if __name__ == "__main__":
    Num = eval(input("Please input a num:"))
    Yanghui_triangle(Num)