from domain.validators import validator_lab, validator_notare, validator_student
from repository.memory import memory_lab, memory_nota, memory_student
from repository.file import file_student, file_lab, file_nota
from services.services import services_lab, services_nota, services_student
from ui.console import console
import unittest

loader = unittest.TestLoader()
start_dir = '/home/mury/Python Stuff/App_Studenti/tests'
suite = loader.discover(start_dir)
runner = unittest.TextTestRunner(verbosity=1)
x=runner.run(suite)

if x.errors or x.failures:
     pass
else: 

    val_stud=validator_student()
    val_lb=validator_lab()
    val_nt=validator_notare()

    repo_stud=memory_student()
    repo_lb=memory_lab()
    repo_nt=memory_nota()
    #repo_stud_file=file_student('/home/mury/Python Stuff/App_Studenti/data/students.txt')
    repo_stud_file=file_student('data/students.txt')
    repo_lb_file=file_lab('data/labs.txt')
    repo_nt_file=file_nota('data/note.txt')

    serv_stud=services_student(repo_stud_file,val_stud)
    serv_lb=services_lab(repo_lb_file,val_lb)
    serv_nt=services_nota(repo_nt_file,repo_stud_file,repo_lb_file,val_nt)


    ui=console(serv_stud,serv_lb,serv_nt)
    ui.show_ui()

