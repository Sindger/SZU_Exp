def MapTransform():
    print(list(map(lambda i:int(i),['12','-2','0'])))
    print(list(map(lambda i: len(i), ['hello', 'world'])))
    print(list(map(lambda i: i[::-1], ['hello', 'world'])))
    print(list(map(lambda i: (i, i ** 2, i ** 3), range(2, 6))))
    print(list(map(lambda i: i[0] * i[1], zip(range(2, 5), range(3, 9, 2)))))

if __name__=="__main__":
    MapTransform()