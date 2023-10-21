from functools import reduce
def ReduceTransform():
    print(reduce(lambda x,y:x if x>y else y,[23,49,6,32]))
    print(reduce(lambda x,y:x+y,['foo', 'bar','baz','quz']))
    print(reduce(lambda x, y: x * y, [2,4,6]))

if __name__=="__main__":
    ReduceTransform()