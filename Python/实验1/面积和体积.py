import math
r=float(input("Enter the radius of a cylinder:"))
h=float(input("Enter the length of a cylinder:"))
S=round(math.pi*r*r,4)
V=round(math.pi*r*r*h,1)
print("The area is",S,"\nThe volume is",V)
