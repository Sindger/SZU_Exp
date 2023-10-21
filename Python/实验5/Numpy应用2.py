import numpy as np
from PIL import Image
import  matplotlib.pyplot as p

image=Image.open('1.jpg')
array=np.array(image)
weight=[0.299,0.587,0.114]
tile=np.tile(weight,reps=(array.shape[0],array.shape[1],1))
im=np.sum(tile*array,axis=2)
im=Image.fromarray(array)
im.save('img_gray.png')

image=Image.open('1.jpg')
array=np.array(image)
r1,r2=np.split(array,2,axis=0)
im=Image.fromarray(r1)
im=im.convert('RGB')
im.save('img_crop.png')

image=Image.open('1.jpg')
array=np.array(image)
array1=array[::-1]
im=Image.fromarray(array1)
im=im.convert('RGB')
im.save('img_flip_vert.png')
