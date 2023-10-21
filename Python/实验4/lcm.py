from functools import reduce
import math
def lcm(*nums):
    return int(reduce(lambda x,y:x*y/math.gcd(int(x),int(y)),nums,1))

if __name__=="__main__":
    num=eval(input("Please input a integer list:"))
    print(lcm(num))