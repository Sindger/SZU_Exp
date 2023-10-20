class Shape:
    def draw(self):
        pass

    def erase(self):
        pass


class Circle(Shape):
    def draw(self):
        print("Draw Circle")

    def erase(self):
        print("Erase Circle")


class Rectangle(Shape):
    def draw(self):
        print("Draw Rectangle")

    def erase(self):
        print("Erase Rectangle")

class Triangle(Shape):
    def draw(self):
        print("Draw Triangle")

    def erase(self):
        print("Erase Triangle")

class ShapeFactory:
    @staticmethod
    def create_shape(shape_type):
        if shape_type == "Circle":
            return Circle()
        elif shape_type == "Rectangle":
            return Rectangle()
        elif shape_type == "Triangle":
            return Triangle()
        else:
            raise ValueError("Unsupported shape type")


if __name__ == "__main__":
    try:
        shape_str = input("Enter the shape type:")
        shape = ShapeFactory.create_shape(shape_str)
        shape.draw()
        shape.erase()
    except ValueError as e:
        print(str(e))
