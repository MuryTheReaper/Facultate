#modului cu operatiile efectuate
from domain.entities import lab_prb, notare, student
from repository.memory import memory_lab, memory_nota, memory_student

class RepoError(Exception):
    pass

class file_student(memory_student):
    #operatii pentru student din fisier
    def __init__(self,filepath):
        super().__init__()
        self.__file=filepath
        
    def __load_file(self):
        #incarca in memorie studentii din fisier
        catalog=[]
        with open(self.__file,'r') as f:
            for line in f:
                if ';' in line:
                    line=line.split(";")
                    id=int(line[0])
                    nume=line[1]
                    grupa=line[2]
                    s=student(nume,grupa)
                    s.set_id(id)
                    catalog.append(s)
                else:
                    student.reset_id(1)
                    student.newid=int(line)
        super().set_catalog(catalog)
    
    def __store_file(self):
        #pune in fisier studentii din memorie
        catalog=super().get_all_students()
        with open(self.__file,'w') as f:
            for s in catalog:
                s_str=str(s.get_id())+';'+s.get_nume()+';'+s.get_grupa()+';\n'
                f.write(s_str)
            f.write(str(student.newid))
        super().set_catalog([])
    
    def delete_file(self):
        with open(self.__file,'w') as f:
            f.write('1\n')

    def add_student(self, student):
        #adauga un student in fisier
        self.__load_file()
        student.set_id(student.newid)
        student.inc_id()
        super().add_student(student)
        self.__store_file()
    
    def remove_student(self, id):
        #sterge un student din fisier
        self.__load_file()
        super().remove_student(id)
        self.__store_file()
    
    def modify_student(self, student):
        #modifica un student din fisier
        self.__load_file()
        super().modify_student(student)
        self.__store_file()
    
    def get_one_student(self, id, n):
        #returneaza un student dupa id din fisier
        self.__load_file()
        x=super().get_one_student(id, n)
        super().set_catalog([])
        return x
    
    def get_all_students(self):
        #returneaza toti studentii din fisier
        self.__load_file()
        l=super().get_all_students()
        super().set_catalog([])
        return l

class file_lab(memory_lab):
    #operatii pentru probleme de laborator din fisier
    def __init__(self,filepath):
        super().__init__()
        self.__file=filepath

    def __load_file(self):
        #incarca in memorie problemele de laborator din fisier
        labs=[]
        with open(self.__file,'r') as f:
            for line in f:
                line=line.split(";")
                nrlb_nrprb=line[0]
                desc=line[1]
                deadline=line[2]
                l=lab_prb(nrlb_nrprb,desc,deadline)
                labs.append(l)
        super().set_labs(labs)

    def __store_file(self):
        #pune in fisier problemele de laborator din memorie
        labs=super().get_all_labs()
        with open(self.__file,'w') as f:
            for l in labs:
                l_str=l.get_nrlb_nrprb()+';'+l.get_desc()+';'+l.get_deadline()+';\n'
                f.write(l_str)
        super().set_labs([])
    
    def delete_file(self):
        with open(self.__file,'w') as f:
            f.write('')
    
    def add_lab(self, lab):
        #adauga in fisier o problema de laborator
        self.__load_file()
        super().add_lab(lab)
        self.__store_file()
    
    def remove_lab(self, nume):
        #sterge in fisier o problema de laborator
        self.__load_file()
        super().remove_lab(nume)
        self.__store_file()
    
    def modify_lab(self, lab):
        #modifica din fisier o problema de laborator
        self.__load_file()
        super().modify_lab(lab)
        self.__store_file()

    def get_one_lab(self, nume, n):
        #returneaza din fisier o problema de laborator
        self.__load_file()
        x=super().get_one_lab(nume, n)
        super().set_labs([])
        return x
    
    def get_all_labs(self):
        #returneaza in fisier tate problemele de laborator
        self.__load_file()
        l=super().get_all_labs()
        super().set_labs([])
        return l

class file_nota(memory_nota):
    #operatiile pentru legaturiile dintre studenti si lab-uri din fisier
    def __init__(self,filepath):   
        super().__init__()
        self.__file=filepath
        #print(self._memory_nota__note)

    def __load_file(self):
        #incarca in memorie legaturile din fisier
        note=[]
        with open(self.__file,'r') as f:
            for line in f:
                line=line.split(";")
                nume=int(line[0])
                nrlb_nrprb=line[1]
                nota=line[2]
                if nota=='None':
                    nota=None
                else: nota=float(nota)
                n=notare(nume,nrlb_nrprb,nota)
                note.append(n)
        super().set_note(note)
    
    def __store_file(self):
        #pune in fisier legaturile din memorie
        note=super().get_all_note()
        with open(self.__file,'w') as f:
            for n in note:
                n_str=str(n.get_student())+';'+n.get_lab()+';'+str(n.get_nota())+';\n'
                f.write(n_str)
        super().set_note([])
    
    def delete_file(self):
        with open(self.__file,'w') as f:
            f.write('')
    
    def asignare(self, nota):
        #assignare lab la student din fisier
        self.__load_file()
        super().asignare(nota)
        self.__store_file()
    
    def add_nota(self, id, lab, nota):
        #noteaza lab-ul unui elev din fisier
        self.__load_file()
        super().add_nota(id,lab,nota)
        self.__store_file()
    
    def remove_asg(self, id,lab):
        #sterge o legatura din fisier dupa id
        self.__load_file()
        super().remove_asg(id,lab)
        self.__store_file()
    
    def get_all_note(self):
        #returneaza lista cu toate notele din fisier
        self.__load_file()
        l=super().get_all_note()
        super().set_note([])
        return l
    
def test_add_student():
    repo=file_student('/home/mury/Python Stuff/App_Studenti/repository/test_students.txt')
    s=student("Y X","215")
    repo.add_student(s)
    s.reset_id()
    list=repo.get_all_students()
    assert list[0]==s
    repo.delete_file()

def test_remove_student():
    repo=file_student('/home/mury/Python Stuff/App_Studenti/repository/test_students.txt')
    s=student("X Y",'215')
    repo.add_student(s)
    repo.remove_student(1)
    s.reset_id()
    list=repo.get_all_students()
    assert list==[]
    repo.delete_file()

def test_modify_student():
    repo=file_student('/home/mury/Python Stuff/App_Studenti/repository/test_students.txt')
    s1=student("X Y",'215')
    s2=student("Y X",'215')
    repo.add_student(s1)
    s2.set_id(1)
    repo.modify_student(s2)
    s1.reset_id()
    list=repo.get_all_students()
    assert list[0]==s2
    repo.delete_file()

def test_get_one_student():
    repo=file_student('/home/mury/Python Stuff/App_Studenti/repository/test_students.txt')
    s=student("X Y",'215')
    repo.add_student(s)
    r=repo.get_one_student(1)
    assert r==s
    s.reset_id()
    repo.delete_file()

def test_add_lab():
    repo=file_lab('/home/mury/Python Stuff/App_Studenti/repository/test_labs.txt')
    l=lab_prb("6_9","FP","08/11/2021")
    repo.add_lab(l)
    list=repo.get_all_labs()
    assert list[0]==l
    repo.delete_file()

def test_remove_lab():
    repo=file_lab('/home/mury/Python Stuff/App_Studenti/repository/test_labs.txt')
    l=lab_prb("6_9","FP","08/11/2021")
    repo.add_lab(l)
    repo.remove_lab("6_9")
    list=repo.get_all_labs()
    assert list==[]
    repo.delete_file()

def test_modify_lab():
    repo=file_lab('/home/mury/Python Stuff/App_Studenti/repository/test_labs.txt')
    l1=lab_prb("1_2","FP","11/11/2011")
    l2=lab_prb("1_3","FP","11/12/2021")
    repo.add_lab(l1)
    l2.set_nrlb_nrprb(l1.get_nrlb_nrprb())
    repo.modify_lab(l2)
    list=repo.get_all_labs()
    assert list[0]==l2
    repo.delete_file()

def test_get_one_lab():
    repo=file_lab('/home/mury/Python Stuff/App_Studenti/repository/test_labs.txt')
    l=lab_prb("1_2","FP","11/11/2021")
    repo.add_lab(l)
    r=repo.get_one_lab("1_2")
    assert r==l
    repo.delete_file()

def test_asignare():
    repo=file_nota('/home/mury/Python Stuff/App_Studenti/repository/test_note.txt')
    n=notare(1,"1_2")
    repo.asignare(n)
    list=repo.get_all_note()
    assert list[0]==n
    repo.delete_file()

def test_add_nota():

    repo=file_nota('/home/mury/Python Stuff/App_Studenti/repository/test_note.txt')
    n=notare(1,"1_2")
    repo.asignare(n)
    list=repo.get_all_note()
    assert list[0].get_nota()==None
    repo.add_nota(1,"1_2",10)
    list=repo.get_all_note()
    assert list[0].get_nota()==10
    repo.delete_file()

def test_remove_asg():

    repo=file_nota('/home/mury/Python Stuff/App_Studenti/repository/test_note.txt')
    n=notare(1,"1_2")
    repo.asignare(n)
    repo.remove_asg(1,"1_2")
    list=repo.get_all_note()
    assert list==[]
    repo.delete_file()

# test_add_student()
# test_remove_student()
# test_modify_student()
# test_get_one_student()
# test_add_lab()
# test_remove_lab()
# test_modify_lab()
# test_get_one_lab()
# test_asignare()
# test_add_nota()
# test_remove_asg()