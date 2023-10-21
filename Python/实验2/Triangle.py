import math
def isValid(side1, side2, side3):
    if (side1 + side2 > side3 and
            side1 + side3 > side2 and
            side2 + side3 > side1 and
            side1 > 0 and
            side2 > 0 and
            side3 > 0):
        return True
    return False

def perimeter(side1,side2,side3):
    return side1+side2+side3

def area(side1,side2,side3):
    p=(side1+side2+side3)/2
    area=math.sqrt(p*(p-side1)*(p-side2)*(p-side3))
    return area