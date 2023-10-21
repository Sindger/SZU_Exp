from PIL import Image,ImageDraw,ImageFont
from random import *
def create():
    text='abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890'
    random_text=""
    for i in range(1,5):
        random_text+=choice(text)
    return random_text

image=Image.new("RGB",(100,50),(randint(0,255),randint(0,255),randint(0,255)))
draw=ImageDraw.Draw(image)
font=ImageFont.truetype(r'C:\Windows\Fonts\simhei.ttf',size=30)
loc=15
for i in create():
    R = str(randint(0, 255))
    G = str(randint(0, 255))
    B = str(randint(0, 255))
    draw.text((loc, 10),
              text=i,
              font=font,
              fill="rgb(" + R + "," + G + "," + B + ")",
              direction=None)
    loc += 20

for i in range(1, randint(7, 14)):
    x1, y1 = randint(0, 100), randint(0, 50)  # 线条起点
    x2, y2 = randint(0, 100), randint(0, 50)  # 线条终点
    R = str(randint(0, 255))
    G = str(randint(0, 255))
    B = str(randint(0, 255))
    draw.line((x1, y1, x2, y2), fill="rgb(" + R + "," + G + "," + B + ")", width=2)

image.show()
image.save("CAPTCHA.png")
