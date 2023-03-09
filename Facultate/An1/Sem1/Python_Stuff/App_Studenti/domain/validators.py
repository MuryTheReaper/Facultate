#validatorii pentru student si lab
from domain.entities import lab_prb, notare, student
from repository.memory import memory_lab, memory_student

class ValidatorException(Exception):
    pass

class validator_student:
    #validatorul pentru student ex: "nume prenume",grupa(numar intre 210 si 217)
    #ridica eroare un string cu erorile care au aparut, daca nu apar nu face nimic
    def student_validate(self,student):
        errors = []
        if len(student.get_nume().split())<2 :
            errors.append("Numele studentului trebuie sa aiba cel putin 2 cuvinte")
        try:
            if not(int(student.get_grupa())>=210 and int(student.get_grupa())<=217):
                raise ValueError
        except ValueError:
            errors.append("Grupa trebuie sa fie un numar intre 210 si 217")
        
        if len(errors)>0:
            errors='\n'.join(errors)
            raise ValidatorException(errors)

class validator_lab:
    #validatorul pentru lab ex: "lb_prb","materie"(o materie din curiculum),"DD/MM/YYYY"
    #ridica eroare un string cu erorile care au aparut, daca nu apar nu face nimic
    def lab_validate(self,lab):
        errors=[]
        try:
            lname=lab.get_nrlb_nrprb().split('_')
            nrlb=int(lname[0])
            nrprb=int(lname[1])
        except:
            errors.append("Laboratorul trebuie sa fie de forma nrlab_nrprb")
        if lab.get_desc() not in ["FP","Algebra","Analiza","ASC","LC"]:
            errors.append("Materia nu se afla in programa (FP,Algebra,Analiza,ASC,LC)")
        try:
            date=lab.get_deadline().split('/')
            day=int(date[0])
            month=int(date[1])
            year=int(date[2])
            if not(day>=1 and day<=31):
                raise ValueError
            if not(month>=1 and month<=12):
                raise ValueError
        except:
            errors.append("Deadline-ul trebuie sa fie de forma DD/MM/YYYY")
        
        if len(errors)>0:
            errors='\n'.join(errors)
            raise ValidatorException(errors)

class validator_notare():
    #validator pentru notare
    def notare_validate(self,nota,ok_s,ok_l):
        errors=[]
        try:
            id=int(nota.get_student())
            if id<1:
                raise ValueError
        except:
            errors.append("ID-ul trebuie sa fie un numar natural")
        try:
            lname=nota.get_lab().split('_')
            nrlb=int(lname[0])
            nrprb=int(lname[1])
        except:
            errors.append("Laboratorul trebuie sa fie de forma nrlab_nrprb")
        if ok_s==False:
            errors.append("Nu exista student cu acest ID")
        if ok_l==False:
            errors.append("Nu exista problema de laborator")
        
        if len(errors)>0:
            errors='\n'.join(errors)
            raise ValidatorException(errors)


def test_student_validate():

    s=student("","")
    try:
        val=validator_student()
        val.student_validate(s)
        assert False
    except ValidatorException as ve:
        e=["Numele studentului trebuie sa aiba cel putin 2 cuvinte","Grupa trebuie sa fie un numar intre 210 si 217"]
        e='\n'.join(e)
        assert str(ve)==str(e)
    finally:
        s.reset_id()

def test_lab_validate():

    l=lab_prb("11","he","99")
    try:
        val=validator_lab()
        val.lab_validate(l)
        assert False
    except ValidatorException as ve:
        e=["Laboratorul trebuie sa fie de forma nrlab_nrprb","Materia nu se afla in programa (FP,Algebra,Analiza,ASC,LC)","Deadline-ul trebuie sa fie de forma DD/MM/YYYY"]
        e='\n'.join(e)
        assert str(ve)==str(e)

def test_notare_validate():

    n=notare("1","1_2")
    try:
        ok_s=False
        ok_l=False
        val=validator_notare()
        val.notare_validate(n,ok_s,ok_l)
        assert False
    except ValidatorException as ve:
        e=["Nu exista student cu acest ID","Nu exista problema de laborator"]
        e='\n'.join(e)
        assert str(ve)==str(e)

test_student_validate()
test_lab_validate()
test_notare_validate()