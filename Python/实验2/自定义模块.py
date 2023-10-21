import Triangle
a=eval(input())
b=eval(input())
c=eval(input())
if Triangle.perimeter(a,b,c):
    print(a,b,c,"能够构成三角形")
    print("构成的三角形的周长是", Triangle.perimeter(a, b, c))
    print("构成的三角形的面积是", Triangle.area(a, b, c))
else:
    print(a,b,c,"不能构成三角形")