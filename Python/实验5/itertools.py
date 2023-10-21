import itertools
def sum0(list):
    for i in range(1,9):
        it=itertools.combinations(list,i)
        for j in it:
            if sum(j)==0:
                return True
    return False

list=[-3,11,21,5,10,11,2,1]
print(sum0(list))
list=[2,3,4,5,6,7,8,9]
print(sum0(list))