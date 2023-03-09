#modului cu operatiile efectuate
from domain.entities import lab_prb, notare, student

class RepoError(Exception):
    pass

class memory_student:
    #operatiile pentru student
    def __init__(self):
        self.__catalog=[]
    
    def set_catalog(self,value):
        self.__catalog=value
    
    def add_student(self, student):
        #adauga un student in memorie
        self.__catalog.append(student)

    def remove_student(self,id):
        #sterge un student din memorie dupa id
        #returneaza true daca s-a sters si false daca nu

        #analizam complexitatea:

        #caz favorabil --> elementul cautat este primul(intructiunile din for se executa doar o data) 
        # T(n) = 1 = theta(1)
        
        #caz defavorabil --> elementul cautat este ultimul sau nu exista
        # T(n) = n = theta(n)

        #caz mediu --> elementul cautat poate fi pe pozitia 1,2,3,...,n (aceeasi probabilitate)
        # T(n) = (1+2+3+...+n)/n = (n+1)/2 = theta(n)

        #Complexitate O(n)

        for el in self.__catalog:
            if el.get_id()==id:
                self.__catalog.remove(el)
                return
        raise RepoError("Nu exista studentul")
    
    def modify_student(self,student):
        #modifica numele si grupa studentului dupa id
        #returneaza true daca s-a modificat si false daca nu
        for i,el in enumerate(self.__catalog):
            if el==student:
                self.__catalog[i]=student
                return
        raise RepoError("Nu exista studentul")
    
    # def get_one_student(self,id):
    #     #cauta un student dupa id
    #     #returneaza studentul gasit
    #     for el in self.__catalog:
    #         if el.get_id()==id:
    #             return el
    #     raise RepoError("Nu exista studentul")

    def get_one_student(self,id,n):

        if n < len(self.__catalog):
            if self.__catalog[n].get_id()==id:
                return self.__catalog[n]
        else:
            raise RepoError("Nu exista studentul")
        
        return self.get_one_student(id,n+1)

    def get_all_students(self):
        #returneaza lista cu toti studentii
        return self.__catalog

class memory_lab:
    #operatiile pentru lab
    def __init__(self):
        self.__labs=[]

    def set_labs(self,value):
        self.__labs=value

    def add_lab(self, lab):
        #adauga un lab in memorie
        if lab not in self.__labs:
            self.__labs.append(lab)
            return
        raise RepoError("Exista deja problema de laborator")
    
    def remove_lab(self,nume):
        #sterge un lab din memorie dupa nume
        #returneaza true daca s-a sters si false daca nu
        for el in self.__labs:
            if el.get_nrlb_nrprb()==nume:
                self.__labs.remove(el)
                return
        raise RepoError("Nu exista problema de laborator")
    
    def modify_lab(self,lab):
        #modifica desc si deadline-ul unui lab care are nrlb_nrprb
        #returneaza true daca s-a modificat si false daca nu
        for i,el in enumerate(self.__labs):
            if el.get_nrlb_nrprb()==lab.get_nrlb_nrprb():
               self.__labs[i]=lab
               return
        raise RepoError("Nu exista problema de laborator")

    # def get_one_lab(self,nume):
    #     #cauta lab dupa nume
    #     #returneaza studentul gasit
    #     for el in self.__labs:
    #         if el.get_nrlb_nrprb()==nume:
    #             return el
    #     raise RepoError("Nu exista problema de laborator")

    def get_one_lab(self,nume,n):

        if n < len(self.__labs):
            if self.__labs[n].get_nrlb_nrprb()==nume:
                return self.__labs[n]
        else:
            raise RepoError("Nu exista problema de laborator")
        
        return self.get_one_lab(nume,n+1)

    def get_all_labs(self):
        #returneaza lista cu toate lab-urile
        return self.__labs

class memory_nota:
    #operatiile pentru legaturiile dintre studenti si lab-uri
    def __init__(self):
        self.__note=[]
    
    def set_note(self,value):
        self.__note=value

    def asignare(self,nota):
        #assignare lab la student
        if nota not in self.__note:
            self.__note.append(nota)
        else:
            raise RepoError("Studentul are deja problema de laborator")
    
    def add_nota(self,id,lab,nota):
        #noteaza lab-ul unui elev
        for el in self.__note:
            if el.get_student()==id and el.get_lab()==lab:
                el.set_nota(nota)
                return
        raise RepoError("Studentul nu are problema de laborator sau nu exista")

    def remove_asg(self,id,lab):
        #sterge o legatura din memorie dupa id
        for el in self.__note:
            if el.get_student()==id and el.get_lab()==lab:
                self.__note.remove(el)
                return 
        raise RepoError("Studentul nu are problema de laborator sau nu exista")   

    def get_all_note(self):
        #returneaza lista cu toate notele
        return self.__note
        
def test_add_student():

    repo=memory_student()
    s=student("X Y",215)
    repo.add_student(s)
    list=repo.get_all_students()
    assert list[0]==s
    s.reset_id()

def test_remove_student():
    
    repo=memory_student()
    s=student("X Y",215)
    repo.add_student(s)
    repo.remove_student(1)
    list=repo.get_all_students()
    assert list==[]
    s.reset_id()

def test_modify_student():

    repo=memory_student()
    s1=student("X Y",215)
    s2=student("Y X",215)
    repo.add_student(s1)
    s2.set_id(1)
    repo.modify_student(s2)
    list=repo.get_all_students()
    assert list[0]==s2
    s1.reset_id()

def test_get_one_student():
    s=student("X Y",215)
    repo=memory_student()
    repo.add_student(s)
    r=repo.get_one_student(1,0)
    assert r==s
    s.reset_id()

def test_add_labs():
    
    repo=memory_lab()
    l=lab_prb("6_9","FP","08/11/2021")
    repo.add_lab(l)
    list=repo.get_all_labs()
    assert list[0]==l

def test_remove_lab():

    repo=memory_lab()
    l=lab_prb("6_9","FP","08/11/2021")
    repo.add_lab(l)
    repo.remove_lab("6_9")
    list=repo.get_all_labs()
    assert list==[]

def test_get_one_lab():
    l=lab_prb("1_2","FP","11/11/2021")
    repo=memory_lab()
    repo.add_lab(l)
    r=repo.get_one_lab("1_2")
    assert r==l

def test_modify_lab():

    repo=memory_lab()
    l1=lab_prb("1_2","FP","11/11/2011")
    l2=lab_prb("1_3","FP","11/12/2021")
    repo.add_lab(l1)
    l2.set_nrlb_nrprb(l1.get_nrlb_nrprb())
    repo.modify_lab(l2)
    list=repo.get_all_labs()
    assert list[0]==l2

def test_asignare():

    repo=memory_nota()
    n=notare(1,"1_2")
    repo.asignare(n)
    list=repo.get_all_note()
    assert list[0]==n

def test_add_nota():

    repo=memory_nota()
    n=notare(1,"1_2")
    repo.asignare(n)
    list=repo.get_all_note()
    assert list[0].get_nota()==None
    repo.add_nota(1,"1_2",10)
    assert list[0].get_nota()==10

def test_remove_asg():

    repo=memory_nota()
    n=notare(1,"1_2")
    repo.asignare(n)
    repo.remove_asg(1,"1_2")
    list=repo.get_all_note()
    assert list==[]

# test_add_student()
# test_add_labs()
# test_remove_student()
# test_remove_lab()
# test_modify_student()
# test_modify_lab()
# test_get_one_student()
# test_get_one_lab()
# test_asignare()
# test_add_nota()
# test_remove_asg()
