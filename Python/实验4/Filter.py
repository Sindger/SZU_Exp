def FilterTransform():
    print(list(filter(lambda i: int(i) >= 0, ['12', '-2', '0'])))
    print(list(filter(lambda i: i[0] == 'w', ['hello', 'world'])))
    print(list(filter(lambda i: i[0] == 't', ['technology', 'method', 'technique'])))
    print(list(filter(lambda i: i % 3 == 0 or i % 5 == 0, range(20))))

if __name__=="__main__":
    FilterTransform()