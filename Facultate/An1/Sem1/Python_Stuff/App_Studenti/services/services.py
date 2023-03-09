#modulul pentru a face conexiunea intre consola si operatie
from domain.dto import student_grade
from domain.entities import notare, student,lab_prb
from domain.validators import validator_lab, validator_notare, validator_student
from repository.file import file_student
from repository.memory import RepoError, memory_lab, memory_nota, memory_student
from utils.sorts import sort_selection, sort_shake

class services_student:
    #intermediarul dintre consola si operatie pentru student
    def __init__(self,repo,val):
        self.__repo=repo
        self.__validator=val
    
    def add_student(self,nume,grupa):
        #adauga un student in memorie
        s=student(nume,grupa)
        self.__validator.student_validate(s)
        self.__repo.add_student(s)
        
    def remove_student(self,id):
        #sterge un student din memorie dupa id
        self.__repo.remove_student(id)

    def modify_student(self,id,nume,grupa):
        #modifica numele si grupa studentului dupa id
        s=student(nume,grupa)
        s.set_id(id)
        s.dec_id()
        self.__validator.student_validate(s)
        self.__repo.modify_student(s)
        
    def get_one_student(self,id):
        #returneaza studentul dorit
        return self.__repo.get_one_student(id,0)

    def get_all_students(self):
        #returneaza lista cu toti studentii
        return self.__repo.get_all_students()

class services_lab:
    #intermediarul pentru lab dintre consola si operatie pentru lab
    def __init__(self,repo,val):
        self.__repo=repo
        self.__validator=val
    
    def add_lab(self,nrlb_nrprb,desc,deadline):
        #adauga un lab in memorie
        l=lab_prb(nrlb_nrprb,desc,deadline)
        self.__validator.lab_validate(l)
        self.__repo.add_lab(l)
    
    def remove_lab(self,nume):
        #sterge un lab din memorie dupa nume
        l=lab_prb(nume,"ASC","11/11/11")
        self.__validator.lab_validate(l)
        self.__repo.remove_lab(nume)

    def modify_lab(self,nrlb_nrprb,desc,deadline):
        #modifica desc si deadline-ul unui lab care are nrlb_nrprb
        l=lab_prb(nrlb_nrprb,desc,deadline)
        self.__validator.lab_validate(l)
        self.__repo.modify_lab(l)
    
    def get_one_lab(self,nume):
        #returneaza lab-ul dorit
        l=lab_prb(nume,"ASC","11/11/11")
        self.__validator.lab_validate(l)
        return self.__repo.get_one_lab(nume,0)

    def get_all_labs(self):
        #returneaza lista cu toate lab-urile
        return self.__repo.get_all_labs()

class services_nota:
    #intermediarul pentru notare dintre consola si operatie pentru notare
    def __init__(self,repo_n,repo_s,repo_l,val):
        self.__repo_n=repo_n
        self.__repo_s=repo_s
        self.__repo_l=repo_l
        self.__validator=val
    
    def asignare(self,id,lab):
        #adauga un lab in memorie
        n=notare(id,lab)
        ok_s=True
        ok_l=True
        try:
            self.__repo_s.get_one_student(id,0)
        except RepoError as re:
            ok_s=False
        try:
            self.__repo_l.get_one_lab(lab,0)
        except RepoError as re:
            ok_l=False

        self.__validator.notare_validate(n,ok_s,ok_l)
        self.__repo_n.asignare(n)
    
    def add_nota(self,id,lab,nota):
        #notare problema de laborator
        n=notare(id,lab)
        self.__validator.notare_validate(n,True,True)
        self.__repo_n.add_nota(id,lab,nota)
    
    def remove_asg(self,id,lab):
        #sterge o legatora de tip student-lab
        n=notare(id,lab)
        self.__validator.notare_validate(n,True,True)
        self.__repo_n.remove_asg(id,lab)
    
    def get_all_note(self):
        #returneaza lista cu toate notele
        return self.__repo_n.get_all_note()
    
    def get_all_noted(self):
        #returneaza lista cu toate notele care au fist notate
        noted=self.__repo_n.get_all_note()
        i=0
        while i<len(noted):
            if noted[i].get_nota()==None:
                noted.remove(noted[i])
            else:
                i+=1
        return noted
    
    def get_all_students_grade(self):
        #
        grades=[]#grades=[[1,2,18],[2,1,8.6]]
        note=self.get_all_noted()
        for nota in note:#note=[(1,"1_2",8),(1,"1_3",10)]
            if nota.get_student() not in (row[0] for row in grades):
                grades.append([nota.get_student(),1,nota.get_nota()])
            else:
                for row in grades:
                    if row[0]==nota.get_student():
                        row[1]+=1
                        row[2]+=nota.get_nota()
                        break
        the_grades=[]
        for row in grades:
            the_grades.append(student_grade(row[0],round(row[2]/row[1],2)))
        return the_grades


    def get_all_note_sort_name(self):
        #returneaza lista cu toate notele sortate alfabetic dupa nume
        new_list=list(self.get_all_students_grade())
        #new_list.sort(key=lambda notare: self.__repo_s.get_one_student(notare.get_student()).get_nume())
        #new_list=sort_selection(new_list,key=lambda notare: self.__repo_s.get_one_student(notare.get_student(),0).get_nume())
        def my_cmp(x,y):
            if self.__repo_s.get_one_student(x.get_student(),0).get_nume() < self.__repo_s.get_one_student(y.get_student(),0).get_nume():
                return -1
            if self.__repo_s.get_one_student(x.get_student(),0).get_nume() > self.__repo_s.get_one_student(y.get_student(),0).get_nume():
                return 1
            if self.__repo_s.get_one_student(x.get_student(),0).get_nume() == self.__repo_s.get_one_student(y.get_student(),0).get_nume():
                if x.get_grade() <= y.get_grade():
                    return -1
                else:
                    return 1
        new_list=sort_selection(new_list,cmp=my_cmp)
        return new_list
    
    def get_all_note_sort_nota(self):
        #returneaza lista cu toate notele sortate descrescator dupa nota
        new_list=list(self.get_all_students_grade())
        #new_list.sort(reverse=True,key=lambda notare: notare.get_grade())
        new_list=sort_shake(new_list,key=lambda notare: notare.get_grade(),reversed=True)
        return new_list
    
    def get_all_note_less_5(self):
        #returneza o lista cu studentii cu note sub 5
        new_list=list(self.get_all_students_grade())
        i=0
        while i<len(new_list):
            if new_list[i].get_grade()>=5:
                new_list.remove(new_list[i])
            else:
                i+=1
        return new_list
    
    def get_all_note_top3(self):
        #returneaza lista cu cele mai multe laburi folosite
        new_list=list(self.get_all_note())
        top3=[]
        for el in new_list:
            nr=1
            if el.get_lab() not in (row[1] for row in top3):
                for x in new_list:
                    if x.get_lab()==el.get_lab() and x!=el:
                        nr+=1
                top3.append([nr,el.get_lab()])
        #top3.sort(key=lambda row:row[0:],reverse=True)
        top3=sort_shake(top3,key=lambda row:row[0:],reversed=True)
        return top3[:3]
            

def test_add_student():
    v=validator_student()
    repo=memory_student()
    serv=services_student(repo,v)
    serv.add_student("X Y",215)
    list=serv.get_all_students()
    assert list[0].get_nume()=="X Y"
    s=student("test",0)
    s.reset_id()

def test_remove_student():
    v=validator_student()
    repo=memory_student()
    serv=services_student(repo,v)
    serv.add_student("X Y",215)
    serv.remove_student(1)
    list=serv.get_all_students()
    assert list==[]
    s=student("test",0)
    s.reset_id()

def test_modify_student():
    v=validator_student()
    repo=memory_student()
    serv=services_student(repo,v)
    serv.add_student("X Y",215)
    list=serv.get_all_students()
    serv.modify_student(1,"M A",215)
    list=serv.get_all_students()
    assert list[0].get_nume()=="M A"
    s=student("test",0)
    s.reset_id()

def test_get_one_student():
    v=validator_student()
    repo=memory_student()
    serv=services_student(repo,v)
    serv.add_student("X Y",215)
    r=serv.get_one_student(1)
    assert r.get_nume()=="X Y"
    r.reset_id()

def test_add_lab():
    v=validator_lab()
    repo=memory_lab()
    serv=services_lab(repo,v)
    serv.add_lab("1_2","FP","11/11/2021")
    list=serv.get_all_labs()
    assert list[0].get_nrlb_nrprb()=="1_2"

def test_remove_lab():
    v=validator_lab()
    repo=memory_lab()
    serv=services_lab(repo,v)
    serv.add_lab("1_2","FP","11/11/2021")
    serv.remove_lab("1_2")
    list=serv.get_all_labs()
    assert list==[]

def test_modify_lab():
    v=validator_lab()
    repo=memory_lab()
    serv=services_lab(repo,v)
    serv.add_lab("1_2","FP","9/11/2021")
    serv.modify_lab("1_2","LC","11/11/2021")
    list=serv.get_all_labs()
    assert list[0].get_deadline()=="11/11/2021"
    assert list[0].get_desc()=="LC"

def test_get_one_lab():
    v=validator_lab()
    repo=memory_lab()
    serv=services_lab(repo,v)
    serv.add_lab("1_2","FP","9/11/2021")
    r=serv.get_one_lab("1_2")
    assert r.get_nrlb_nrprb()=="1_2"
    assert r.get_desc()=="FP"

def test_asignare():

    v_s=validator_student()
    repo_s=memory_student()
    serv_s=services_student(repo_s,v_s)
    serv_s.add_student("X Y",215)
    student.newid=1

    v_l=validator_lab()
    repo_l=memory_lab()
    serv_l=services_lab(repo_l,v_l)
    serv_l.add_lab("1_2","FP","11/11/2021")

    v=validator_notare()
    repo=memory_nota()
    serv=services_nota(repo,repo_s,repo_l,v)
    serv.asignare(1,"1_2")
    list=serv.get_all_note()
    assert list[0].get_student()==1
    assert list[0].get_lab()=="1_2"

def test_add_nota():

    v_s=validator_student()
    repo_s=memory_student()
    serv_s=services_student(repo_s,v_s)
    serv_s.add_student("X Y",215)
    student.newid=1

    v_l=validator_lab()
    repo_l=memory_lab()
    serv_l=services_lab(repo_l,v_l)
    serv_l.add_lab("1_2","FP","11/11/2021")

    v=validator_notare()
    repo=memory_nota()
    serv=services_nota(repo,repo_s,repo_l,v)
    serv.asignare(1,"1_2")
    serv.add_nota(1,"1_2",10)
    list=serv.get_all_note()
    assert list[0].get_nota()==10

def test_remove_asg():

    v_s=validator_student()
    repo_s=memory_student()
    serv_s=services_student(repo_s,v_s)
    serv_s.add_student("X Y",215)
    student.newid=1

    v_l=validator_lab()
    repo_l=memory_lab()
    serv_l=services_lab(repo_l,v_l)
    serv_l.add_lab("1_2","FP","11/11/2021")

    v=validator_notare()
    repo=memory_nota()
    serv=services_nota(repo,repo_s,repo_l,v)
    serv.asignare(1,"1_2")
    serv.remove_asg(1,"1_2")
    list=serv.get_all_note()
    assert list==[]

def test_get_all_note_sort_name():

    v_s=validator_student()
    repo_s=file_student('/home/mury/Python Stuff/App_Studenti/repository/test_students.txt')
    serv_s=services_student(repo_s,v_s)
    serv_s.add_student("X Y",215)
    serv_s.add_student("A B",217)
    student.newid=1

    v_l=validator_lab()
    repo_l=memory_lab()
    serv_l=services_lab(repo_l,v_l)
    serv_l.add_lab("1_2","FP","11/11/2021")
    serv_l.add_lab("1_3","LC","11/11/2021")

    v=validator_notare()
    repo=memory_nota()
    serv=services_nota(repo,repo_s,repo_l,v)
    serv.asignare(1,"1_2")
    serv.asignare(1,"1_3")
    serv.asignare(2,"1_3")
    serv.add_nota(1,"1_2",3)
    serv.add_nota(2,"1_3",2)
    serv.add_nota(1,"1_3",4)
    list=serv.get_all_note_sort_name()

    assert list[0].get_student()==2

def test_get_all_note_sort_nota():

    v_s=validator_student()
    repo_s=memory_student()
    serv_s=services_student(repo_s,v_s)
    serv_s.add_student("X Y",215)
    serv_s.add_student("A B",217)
    student.newid=1

    v_l=validator_lab()
    repo_l=memory_lab()
    serv_l=services_lab(repo_l,v_l)
    serv_l.add_lab("1_2","FP","11/11/2021")
    serv_l.add_lab("1_3","LC","11/11/2021")

    v=validator_notare()
    repo=memory_nota()
    serv=services_nota(repo,repo_s,repo_l,v)
    serv.asignare(1,"1_2")
    serv.asignare(2,"1_3")
    serv.add_nota(1,"1_2",8.7)
    serv.add_nota(2,"1_3",9.6)
    list=serv.get_all_note_sort_nota()
    assert list[0].get_student()==2

def test_get_all_less_5():
    
    v_s=validator_student()
    repo_s=memory_student()
    serv_s=services_student(repo_s,v_s)
    serv_s.add_student("X Y",215)
    serv_s.add_student("A B",217)
    student.newid=1

    v_l=validator_lab()
    repo_l=memory_lab()
    serv_l=services_lab(repo_l,v_l)
    serv_l.add_lab("1_2","FP","11/11/2021")
    serv_l.add_lab("1_3","LC","11/11/2021")

    v=validator_notare()
    repo=memory_nota()
    serv=services_nota(repo,repo_s,repo_l,v)
    serv.asignare(1,"1_2")
    serv.asignare(2,"1_3")
    serv.add_nota(1,"1_2",6)
    serv.add_nota(2,"1_3",10)
    list=serv.get_all_note_less_5()
    assert list==[]

def test_get_all_note_top3():
    v_s=validator_student()
    repo_s=memory_student()
    serv_s=services_student(repo_s,v_s)
    serv_s.add_student("X Y",215)
    serv_s.add_student("A B",217)
    student.newid=1

    v_l=validator_lab()
    repo_l=memory_lab()
    serv_l=services_lab(repo_l,v_l)
    serv_l.add_lab("1_2","FP","11/11/2021")
    serv_l.add_lab("1_3","LC","11/11/2021")

    v=validator_notare()
    repo=memory_nota()
    serv=services_nota(repo,repo_s,repo_l,v)
    serv.asignare(1,"1_2")
    serv.asignare(2,"1_2")
    serv.asignare(1,"1_3")

    assert serv.get_all_note_top3()[0][0]==2
    
# test_add_student()
# test_modify_student()
# test_remove_student()
# test_add_lab()
# test_remove_lab()
# test_modify_lab()
# test_get_one_student()
# test_get_one_lab()
# test_asignare()
# test_add_nota()
# test_remove_asg()
# test_get_all_note_sort_name()
# test_get_all_note_sort_nota()
# test_get_all_less_5()
# test_get_all_note_top3()