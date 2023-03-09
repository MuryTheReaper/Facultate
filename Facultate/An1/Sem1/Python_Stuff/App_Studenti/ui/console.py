#modulul pentru interactionare cu utilizatorul
from termcolor import colored
from domain.validators import ValidatorException
from domain.entities import student
from repository.memory import RepoError
import random
import string

class console:
    
    def __init__(self, serv1,serv2,serv3):
        self.__serv_student = serv1
        self.__serv_lab = serv2
        self.__serv_note = serv3
    
    def __add_student(self):
        try:
            nume=input("Numele studentului: ")
            grupa=input("Grupa studentului: ")
            self.__serv_student.add_student(nume,grupa)
            print(colored("S-a adaugat cu succes",'green'))
        except ValidatorException as ve:
            print(colored(str(ve),'red'))
            student.newid-=1
    
    def __add_lab(self):
        try:
            nrlb_nrprb=input("Laboratorul si problema: ")
            desc=input("Materia: ")
            deadline=input("Deadline-ul: ")
            self.__serv_lab.add_lab(nrlb_nrprb,desc,deadline)
            print(colored("S-a adaugat cu succes",'green'))
        except RepoError as re:
            print(colored(str(re),'red'))
        except ValidatorException as ve:
            print(colored(str(ve),'red'))

    def __asignare(self):
        try:
            id=int(input("ID-ul studentului: "))
            lab=input("Problema de laborator: ")
            self.__serv_note.asignare(id,lab)
            print(colored("S-a asignat cu succes",'green'))
        except ValidatorException as ve:
            print(colored(str(ve),'red'))
        except RepoError as re:
            print(colored(str(re),'red'))
        except ValueError:
            print(colored("ID-ul este un numar natural pozitiv",'red'))

    def __add_nota(self):
        try:
            id=int(input("ID-ul studentului: "))
            if id<1:
                raise ValueError
        except ValueError:
            print(colored("ID este un numar natural pozitiv",'red'))
            
        try:
            lab=input("Problema de laborator: ")
            nota=float(input("Nota obtinuta: "))
            if nota<1 or nota>10:
                raise ValueError
            self.__serv_note.add_nota(id,lab,nota)
            print(colored("S-a notat cu succes",'green'))
        except RepoError as re:
            print(colored(str(re),'red'))
        except ValueError:
            print(colored("Nota este un numar intre 1 si 10",'red'))
        except ValidatorException as ve:
            print(colored(str(ve),'red'))

    def __remove_student(self):
        try:
            id=int(input("ID-ul studentului: "))
            if id<1:
                raise ValueError
            self.__serv_student.remove_student(id)
            print(colored("S-a sters cu succes",'green'))
        except RepoError as re:
            print(colored(str(re),'red'))
        except ValueError:
            print(colored("ID-ul este un numar natural pozitiv",'red'))
        try:
            self.__serv_note.remove_asg(id)
        except:
            pass
    
    def __remove_lab(self):
        try:
            nume=input("Laboratorul si problema: ")
            self.__serv_lab.remove_lab(nume)
            print(colored("S-a sters cu succes",'green'))
        except RepoError as re:
            print(colored(str(re),'red'))
        except ValidatorException as ve:
            print(colored(str(ve),'red'))
        try:
            list_asg=self.__serv_note.get_all_note()
            for el in list_asg:
                if el.get_lab()==nume:
                    self.__serv_note.remove_asg(el.get_student())
        except:
            pass

    def __remove_asg(self):
        try:
            id=int(input("ID-ul studentului: "))
            if id<1:
                raise ValueError
            lab=input("Problema de laborator: ")
            self.__serv_note.remove_asg(id,lab)
            print(colored("S-a sters cu succes",'green'))
        except RepoError as re:
            print(colored(str(re),'red'))
        except ValueError:
            print(colored("ID este un numar natural pozitiv",'red'))
        except ValidatorException as ve:
            print(colored(str(ve),'red'))


    def __modify_student(self):
        try:
            id=int(input("ID-ul studentului: "))
            if id<1:
                raise ValueError
            nume=input("Numele nou: ")
            grupa=input("Grupa noua: ")
            self.__serv_student.modify_student(id,nume,grupa)
            print(colored("S-a modificat cu succes",'green'))
        except RepoError as re:
            print(colored(re),'red')
        except ValidatorException as ve:
            print(colored(str(ve),'red'))
        except ValueError:
            print(colored("ID-ul este un numar natural pozitiv",'red'))
    
    def __modify_lab(self):
        try:
            nrlb_nrprb=input("Laboratorul si problema: ")
            desc=input("Materia noua: ")
            deadline=input("Deadline-ul nou: ")
            self.__serv_lab.modify_lab(nrlb_nrprb,desc,deadline)
            print(colored("S-a modificat cu succes",'green'))
        except RepoError as re:
            print(colored(str(re),'red'))
        except ValidatorException as ve:
            print(colored(str(ve),'red'))

    def __show_one_student(self):
        try:
            id=int(input("ID-ul studentului: "))
            if id<1:
                raise ValueError
            print(self.__serv_student.get_one_student(id))
        except RepoError as re:
            print(colored(str(re),'red'))
        except ValueError:
            print(colored("ID-ul este un numar natural pozitiv",'red'))

    def __show_one_lab(self):
        try:
            nume=input("Problema si laboratorul: ")
            print(self.__serv_lab.get_one_lab(nume))
        except RepoError as re:
            print(colored(str(re),'red'))
        except ValidatorException as ve:
            print(colored(str(ve),'red'))
            
    def __show_all_students(self):
        student_list=self.__serv_student.get_all_students()
        if len(student_list)==0:
            print("Nu exista studenti")
        else:
            for el in student_list:
                print(el)

    def __show_all_labs(self):
        lab_list=self.__serv_lab.get_all_labs()
        if len(lab_list)==0:
            print("Nu exista problema de laborator")
        else:
            for el in lab_list:
                print(el)
    
    def __show_all_assigments(self):
        asg_list=self.__serv_note.get_all_note()
        if len(asg_list)==0:
            print("Nu exista teme")
        else:
            for el in asg_list:
                print(el)

    def __raport_sort_name(self):
        #afiseaza numele studentului si nota luata
        list=self.__serv_note.get_all_note_sort_name()
        if len(list):
            for el in list:
                nume=self.__serv_student.get_one_student(el.get_student()).get_nume()
                nota=el.get_grade()
                print(nume+" are nota: "+str(nota))
        else:
            print(colored("Studentii nu au note",'red'))

    def __raport_sort_nota(self):
        #afiseaza numele studentilor si nota luata
        list=self.__serv_note.get_all_note_sort_nota()
        if len(list):
            for el in list:
                nume=self.__serv_student.get_one_student(el.get_student()).get_nume()
                nota=el.get_grade()
                print(nume+" are nota: "+str(nota))
        else:
            print(colored("Studentii nu au note",'red'))

    def __raport_failed(self):
        #afiseaza numele studentilor care au nota sub 5
        list=self.__serv_note.get_all_note_less_5()
        if len(list):
            for el in list:
                nume=self.__serv_student.get_one_student(el.get_student()).get_nume()
                nota=el.get_grade()
                print(nume+" are nota: "+str(nota))
        else:
            print(colored("Nu sunt studenti cu nota sub 5",'red'))

    def __raport_top3(self):
        #afiseaza top3 cele mai folosite probleme de laborator
        list=self.__serv_note.get_all_note_top3()
        if len(list):
            for el in list:
                lab=self.__serv_lab.get_one_lab(el[1])
                print(lab,"-->",el[0])
        else:
            print(colored("Studentii nu au probleme",'red'))

    def __help(self):
        print("Comenzi disponibile:")
        print("add [student/lab]")
        print("show [all/one] [student/lab/assignment]")
        print("remove [student/lab/assignment]")
        print("modify [student/lab]")
        print("assign [student/nota]")
        print("generate [student/lab/database]")
        print("raport [sort/failed/top3] [sort: name/nota]")
        print("exit")

    def __generate_database(self):
        #functie de generat studenti si lab-uri  
        #functie care ajuta la testing
        self.__serv_student.add_student("M A",'215')
        self.__serv_student.add_student("V C",'217')
        self.__serv_student.add_student("M G",'211')
        self.__serv_lab.add_lab("1_2","FP","11/11/2021")
        self.__serv_lab.add_lab("2_8","LC","09/07/2021")
        self.__serv_lab.add_lab("7_10","Analiza","01/01/2022")
        print(colored("S-au generat studenti si lab-uri pentru testing",'green'))
    
    def __generate_random_student(self):
        #functie de generat studenti random
        letters_up=string.ascii_uppercase
        letters_down=string.ascii_lowercase
        l=random.randint(2,6)
        nume=random.choice(letters_up)+''.join(random.choice(letters_down) for i in range(l))+' '+random.choice(letters_up)+''.join(random.choice(letters_down) for i in range(l))
        grupa=str(random.randint(210,217))
        try:
            self.__serv_student.add_student(nume,grupa)
            print(colored("S-a generat student random",'green'))
        except ValidatorException as ve:
            print(colored(str(ve),'red'))
            student.newid-=1
    
    def __generate_random_lab(self):
        #functie de generat lab-uri random
        nrlb_nrprb=str(random.randint(1,100))+"_"+str(random.randint(1,100))
        desc=random.choice(["FP","Algebra","Analiza","ASC","LC"])
        deadline=str(random.randint(1,31))+"/"+str(random.randint(1,12))+"/"+str(random.randint(0,9001))
        try:
            self.__serv_lab.add_lab(nrlb_nrprb,desc,deadline)
            print(colored("S-a generat lab random",'green'))
        except ValidatorException as ve:
            print(colored(str(ve),'red'))

    def show_ui(self):
        while True:
            cmd = input("Introduceti comanda: ")
            cmd = cmd.lower()
            cmd = cmd.split()
            try:
                if cmd[0]=='help':
                    self.__help()
                elif cmd[0]=='add' and cmd[1]=='student':
                    self.__add_student()
                elif cmd[0]=='add' and cmd[1]=='lab':
                    self.__add_lab()
                elif cmd[0]=='show' and cmd[1]=='all' and cmd[2]=='student':
                    self.__show_all_students()
                elif cmd[0]=='show' and cmd[1]=='one' and cmd[2]=='student':
                    self.__show_one_student()
                elif cmd[0]=='show' and cmd[1]=='all' and cmd[2]=='lab':
                    self.__show_all_labs()
                elif cmd[0]=='show' and cmd[1]=='one' and cmd[2]=='lab':
                    self.__show_one_lab()
                elif cmd[0]=='show' and cmd[1]=='all' and cmd[2]=='assignment':
                    self.__show_all_assigments()
                elif cmd[0]=='remove' and cmd[1]=='student':
                    self.__remove_student()
                elif cmd[0]=='remove' and cmd[1]=='lab':
                    self.__remove_lab()
                elif cmd[0]=='remove' and cmd[1]=='assignment':
                    self.__remove_asg()
                elif cmd[0]=='modify' and cmd[1]=='student':
                    self.__modify_student()
                elif cmd[0]=='modify' and cmd[1]=='lab':
                    self.__modify_lab()
                elif cmd[0]=='assign' and cmd[1]=='student':
                    self.__asignare()
                elif cmd[0]=='assign' and cmd[1]=='nota':
                    self.__add_nota()
                elif cmd[0]=="generate" and cmd[1]=='database':
                    self.__generate_database()
                elif cmd[0]=='generate' and cmd[1]=='student':
                    self.__generate_random_student()
                elif cmd[0]=='generate' and cmd[1]=='lab':
                    self.__generate_random_lab()
                elif cmd[0]=='raport' and cmd[1]=='sort' and cmd[2]=='name':
                    self.__raport_sort_name()
                elif cmd[0]=='raport' and cmd[1]=='sort' and cmd[2]=='nota':
                    self.__raport_sort_nota()
                elif cmd[0]=='raport' and cmd[1]=='failed':
                    self.__raport_failed()
                elif cmd[0]=='raport' and cmd[1]=='top3':
                    self.__raport_top3()
                elif cmd[0]=='exit':
                    return
                else:
                    print(colored('Comanda invalida', 'red'))
                print()
            except IndexError:
                print(colored('Comanda incompleta', 'red'))

            
