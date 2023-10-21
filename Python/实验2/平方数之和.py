def checkSumOfSquareNumbers(c):
    for i in range(1,c):
        for j in range(1,i+1):
            if i**2+j**2==c**2:
                return True
    return False

c=eval(input())
print(checkSumOfSquareNumbers(c))