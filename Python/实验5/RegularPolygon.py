import math
class RegularPolygon():
    def __init__(self,n1=3,side1=1,x1=0,y1=0):
        self.n=n1
        self.side=side1
        self.x=x1
        self.y=y1

    def getPerimeter(self):
        return self.n*self.side

    def getArea(self):
        return 0.25*self.n*\
               self.side*\
               self.side/\
               math.tan(math.pi/self.n)

    def distanceToPolygon(self,p):
        return math.sqrt((self.x-p.x)**2+(self.y-p.y)**2)

    def __str__(self):
        return "这是一个正"+str(self.n)+"边形\n"+"每条边的长度为："+str(self.side)+"\n"+"该多边形的中心为"+"("+str(self.x)+","+str(self.y)+")\n"


if __name__=="__main__":
    polygon1=RegularPolygon()
    print(polygon1)
    polygon2=RegularPolygon(5,4,3,3)
    print(polygon2)
    print("Polygon1的周长为"+str(polygon1.getPerimeter()))
    print("Polygon1的面积为"+str(polygon1.getArea()))
    print("Polygon2的周长为" + str(polygon2.getPerimeter()))
    print("Polygon2的面积为" + str(polygon2.getArea()))
    print("两个多边形中心的距离是"+str(polygon1.distanceToPolygon(polygon2)))
