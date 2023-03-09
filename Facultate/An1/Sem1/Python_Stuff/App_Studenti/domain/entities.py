#modulul pentru tipurile de date (student, lab, clasa de legatura)

class student:
    #clasa de tip student
    newid=1
    def __init__(self,nume,grupa):
        self.__nume=nume
        self.__grupa=grupa
        self.__id=student.newid
        student.newid+=1

    def get_nume(self):
        return self.__nume
    
    def get_grupa(self):
        return self.__grupa
    
    def get_id(self):
        return self.__id
    
    def set_nume(self,value):
        self.__nume=value
    
    def set_grupa(self,value):
        self.__grupa=value
    
    def set_id(self,value):
        self.__id=value
    
    def reset_id(self):
        student.newid=1
    
    def dec_id(self):
        student.newid-=1
    
    def inc_id(self):
        student.newid+=1
    
    def __eq__(self,other):
        if self.__id==other.get_id():
            return True
        return False

    def __str__(self):
        return str(self.__id)+": "+str(self.__nume)+", grupa "+str(self.__grupa)

class lab_prb:
    #clasa de tip lab
    def __init__(self,nrlb_nrprb,desc,deadline):
        self.__nrlb_nrprb=nrlb_nrprb
        self.__desc=desc
        self.__deadline=deadline
    
    def get_nrlb_nrprb(self):
        return self.__nrlb_nrprb
    
    def get_desc(self):
        return self.__desc

    def get_deadline(self):
        return  self.__deadline
    
    def set_nrlb_nrprb(self,value):
        self.__nrlb_nrprb=value
    
    def set_desc(self,value):
        self.__desc=value

    def set_deadline(self,value):
        self.__deadline=value
    
    def __eq__(self,other):
        if self.__nrlb_nrprb==other.get_nrlb_nrprb():
            return True
        return False

    def __str__(self):
        return str(self.__nrlb_nrprb)+": "+str(self.__desc)+", pana la "+str(self.__deadline)

class notare:
    #asignare student-lab
    def __init__(self,student,lab,nota=None):
        self.__student=student
        self.__lab=lab
        self.__nota=nota
    
    def get_student(self):
        return self.__student
    
    def get_lab(self):
        return self.__lab
    
    def get_nota(self):
        return self.__nota

    def set_student(self,value):
        self.__student=value
    
    def set_lab(self,value):
        self.__lab=value
    
    def set_nota(self,value):
        self.__nota=value
    
    def __eq__(self, other):
        if self.__student==other.get_student() and self.__lab==other.get_lab():
            return True
        return False

    def __str__(self):
        if self.__nota==None:
            return "Studentul cu ID: "+str(self.__student)+" are problema de laborator "+str(self.__lab)
        return "Studentul cu ID: "+str(self.__student)+" are problema de laborator "+self.__lab+" cu nota "+str(self.__nota)

def test_student():

    s=student("X Y",215)
    assert s.get_id()==1
    assert s.get_nume()=="X Y"
    assert s.get_grupa()==215
    s2=student("Y X",215)
    assert s2.get_id()==2
    s.reset_id()

def test_lab_prb():

    l=lab_prb("1_1","ASC","21/01/2019")
    assert l.get_nrlb_nrprb()=="1_1"
    assert l.get_desc()=="ASC"
    assert l.get_deadline()=="21/01/2019"

def test_notare():
    n=notare(1,"1_2")
    assert n.get_student()==1
    assert n.get_lab()=="1_2"
    n=notare(2,"2_1",10)
    assert n.get_student()==2
    assert n.get_lab()=="2_1"
    assert n.get_nota()==10
    assert str(n)=="Studentul cu ID: 2 are problema de laborator 2_1 cu nota 10"

#test_student()
#test_lab_prb()
#test_notare()
#if __name__ == '__main__': 
   # unittest.main()

