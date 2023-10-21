from tkinter import *
from random import *

def display():
    canvas.delete('all')
    for i in range(10):
        xpos=randint(50,650)
        ypos=randint(50,450)
        radius=10
        r=randint(0,255)
        g=randint(0,255)
        b=randint(0,255)
        color="#%02x%02x%02x"%(r,g,b)
        canvas.create_oval(xpos,ypos,xpos+radius,ypos+radius,fill=color,outline="black",tag="ball")

if __name__=="__main__":
    root=Tk()
    root.title("Balls")
    label=Label(root,text="Get Balls")
    label.pack()
    root.minsize(800,600)
    root.maxsize(800,600)
    canvas=Canvas(root,width=700,height=500)
    canvas.pack()
    button=Button(root,text="Display",command=display)
    button.pack()
    root.mainloop()