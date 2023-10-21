# -*- coding:utf-8 -*-

class Person(object):
    def __init__(self, name='', age=20, sex='man'):
        self.name_=name
        self.age_=age
        self.sex_=sex

    def setName(self, name):
        self.name_=name

    def setAge(self, age):
        self.age_=age

    def setSex(self, sex):
        self.sex_=sex

    def show(self):
        print("Name:"+str(self.name_))
        print("Age:"+str(self.age_))
        print("Sex:"+str(self.sex_)+"\n")


class Teacher(Person):
    def __init__(self, name='', age=30, sex='man', department='Computer'):
        Person.__init__(self, name, age, sex)
        self.setDepartment(department)

    def setDepartment(self, department):
        self.department_=department

    def show(self):
        print("Name:" + str(self.name_))
        print("Age:" + str(self.age_))
        print("Sex:" + str(self.sex_))
        print("Department:"+str(self.department_)+"\n")


if __name__ == '__main__':
    zhangsan = Person('Zhang San', 19, 'man')
    zhangsan.show()

    lisi = Teacher('Li Xi', 32, 'man', 'Math')
    lisi.show()
    lisi.setAge(40)
    lisi.setName("Li Si")
    lisi.show()
