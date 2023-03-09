#modulul pentru data transfer objects(dto)
class student_grade():
    def __init__(self,student,grade):
        self.__student=student
        self.__grade=grade
    
    def get_student(self):
        return self.__student
    
    def get_grade(self):
        return self.__grade

    def set_student(self,value):
        self.__student=value
    
    def set_grade(self,value):
        self.__grade=value