class Stack():
    def __init__(self,size1=0):
        self.content=[]
        self.size=size1
        self.current=0

    def isempty(self):
        if self.current==0:
            return True
        return False

    def empty(self):
        self.content.clear()
        self.current=0

    def setSize(self,size1):
        if size1<=0:
            print("栈的大小非法")
            return
        self.size=size1
        while self.size<self.current:
            self.pop()

    def isFull(self):
        return self.current==self.size

    def push(self,num):
        if self.isFull():
            print("栈满，请扩充栈的大小")
            return
        self.current+=1
        self.content.append(num)

    def pop(self):
        if self.isempty():
            print("栈空，请插入数据")
            return
        self.current -= 1
        number=self.content[self.current]
        del self.content[self.current]
        return number

    def show(self):
        print("栈的大小为%d/%d"%(self.current,self.size))
        print("栈内元素为"+str(self.content))

if __name__=="__main__":
    size=eval(input("请输入栈的大小:"))
    stack1=Stack(size)
    for i in range(0,6):
        stack1.push(i)
        stack1.show()
    for i in range(0,6):
        stack1.pop()
        stack1.show()
    stack1.setSize(10)
    for i in range(0,10):
        stack1.push(i)
    stack1.show()
    stack1.setSize(5)
    stack1.show()