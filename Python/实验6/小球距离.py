import math
from tkinter import *
from tkinter import messagebox

class circle:
    def __init__(self):
        root=Tk()
        root.title('Ciecle')
        root.minsize(800, 600)
        root.maxsize(800, 600)
        label = Label(root, text="Get Distance")
        label.pack()
        self.canvas=Canvas(root,width=700,height=500)
        self.canvas.pack()
        self.x1=150
        self.y1=150
        self.x2=350
        self.y2=350
        self.r=20
        self.display()
        self.canvas.bind("<B1-Motion>", self.MouseEvent)
        root.mainloop()

    def get_distance(self):
        return math.sqrt((self.x1-self.x2)**2+(self.y1-self.y2)**2)

    def display(self):
        self.canvas.delete('all')
        self.canvas.create_oval(self.x1 - self.r, self.y1 - self.r, self.x1 + self.r, self.y1 + self.r, fill='red',tag='circle1', )
        self.canvas.create_oval(self.x2 - self.r, self.y2 - self.r, self.x2 + self.r, self.y2 + self.r, fill='red',tag='circle2', )
        self.canvas.create_line(self.x1, self.y1, self.x2, self.y2, tags='line')
        self.canvas.create_text((self.x1 + self.x2) / 2, (self.y1 + self.y2) / 2, text="{:.2f}".format(self.get_distance()),tags='distance')

    def illegal(self):
        messagebox.showinfo("Illegal position","Please move again")
        self.x1=150
        self.y1=150
        self.x2=350
        self.y2=350
        self.display()

    def MouseEvent(self, event):
        xpos, ypos = event.x, event.y
        if self.x1 - self.r < xpos < self.x1 + self.r and self.y1 - self.r < ypos < self.y1 + self.r:
            if self.get_distance() <= 2 * self.r:
                self.illegal()
                return
            self.x1 = xpos
            self.y1 = ypos
            self.display()

        elif self.x2 - self.r < xpos < self.x2 + self.r and self.y2 - self.r < ypos < self.y2 + self.r:
            if self.get_distance() <= 2 * self.r:
                self.illegal()
                return
            self.x2 = xpos
            self.y2 = ypos
            self.display()

if __name__=="__main__":
    circle()