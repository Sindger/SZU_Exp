import os

import PIL.Image as Image

IMAGES_PATH = r'C:\Users\Sindger\Desktop\R\\'
IMAGES_FORMAT = ['.jpg', '.JPG']
IMAGE_SIZE = 256
IMAGE_SAVE_PATH = r'C:\Users\Sindger\Desktop\R\final.jpg'

image_names = [name for name in os.listdir(IMAGES_PATH) for item in IMAGES_FORMAT if
               os.path.splitext(name)[1] == item]

print("image_names", image_names)
if len(image_names) != 4:
    raise ValueError("The number of images is error!")

def image_compose():
    to_image = Image.new('RGB', (2 * IMAGE_SIZE, 2 * IMAGE_SIZE))
    for y in range(1, 3):
        for x in range(1, 3):
            from_image = Image.open(IMAGES_PATH + image_names[2 * (y - 1) + x - 1]).resize(
                (IMAGE_SIZE, IMAGE_SIZE), Image.ANTIALIAS)
            to_image.paste(from_image, ((x - 1) * IMAGE_SIZE, (y - 1) * IMAGE_SIZE))
    return to_image.save(IMAGE_SAVE_PATH)

image_compose()