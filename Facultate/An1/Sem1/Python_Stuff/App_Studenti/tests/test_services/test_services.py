import unittest
from domain.entities import student
from domain.validators import validator_lab, validator_notare, validator_student
from repository.memory import memory_lab, memory_nota, memory_student
from services.services import services_lab, services_nota, services_student

class testcase_services_student(unittest.TestCase):
    def setUp(self):
        self.val=validator_student()
        self.repo=memory_student()
        self.serv=services_student(self.repo,self.val)
        self.serv.add_student("X Y",215)
    
    def tearDown(self):
        student.newid=1
    
    def test_add_student(self):
        all=self.serv.get_all_students()
        self.assertEqual(all[0].get_nume(),"X Y")
    
    def test_remove_student(self):
        self.serv.remove_student(1)
        all=self.serv.get_all_students()
        self.assertEqual(all,[])
    
    def test_modify_student(self):
        self.serv.modify_student(1,"M A",215)
        all=self.serv.get_all_students()
        self.assertEqual(all[0].get_nume(),"M A")
    
    def test_get_one_student(self):
        r=self.serv.get_one_student(1)
        self.assertEqual(r.get_nume(),"X Y")

class testcase_services_lab(unittest.TestCase):
    def setUp(self):
        self.val=validator_lab()
        self.repo=memory_lab()
        self.serv=services_lab(self.repo,self.val)
        self.serv.add_lab("1_2","FP","11/11/2021")
    
    def tearDown(self):
        pass
    
    def test_add_lab(self):
        all=self.serv.get_all_labs()
        self.assertEqual(all[0].get_nrlb_nrprb(),"1_2")
    
    def test_remove_lab(self):
        self.serv.remove_lab("1_2")
        all=self.serv.get_all_labs()
        self.assertEqual(all,[])
    
    def test_modify_lab(self):
        self.serv.modify_lab("1_2","LC","11/11/2021")
        all=self.serv.get_all_labs()
        self.assertEqual(all[0].get_deadline(),"11/11/2021")
        self.assertEqual(all[0].get_desc(),"LC")
    
    def test_get_one_lab(self):
        r=self.serv.get_one_lab("1_2")
        self.assertEqual(r.get_nrlb_nrprb(),"1_2")
        self.assertEqual(r.get_desc(),"FP")

class testcase_memory_notare(unittest.TestCase):
    def setUp(self):
        self.val_s=validator_student()
        self.val_l=validator_lab()
        self.val=validator_notare()

        self.repo_s=memory_student()
        self.repo_l=memory_lab()
        self.repo=memory_nota()

        self.serv_s=services_student(self.repo_s,self.val_s)
        self.serv_l=services_lab(self.repo_l,self.val_l)
        self.serv=services_nota(self.repo,self.repo_s,self.repo_l,self.val)

        self.serv_s.add_student("X Y",215)
        self.serv_l.add_lab("1_2","FP","11/11/2021")
        self.serv.asignare(1,"1_2")
    
    def tearDown(self):
        student.newid=1
    
    def test_asignare(self):
        all=self.serv.get_all_note()
        self.assertEqual(all[0].get_student(),1)
        self.assertEqual(all[0].get_lab(),"1_2")
    
    def test_add_nota(self):
        self.serv.add_nota(1,"1_2",10)
        all=self.serv.get_all_note()
        self.assertEqual(all[0].get_nota(),10)
    
    def test_remove_asg(self):
        self.serv.remove_asg(1,"1_2")
        all=self.serv.get_all_note()
        self.assertEqual(all,[])
    
    def test_get_all_note_sort_name(self):
        self.serv_s.add_student("A B",217)
        self.serv_l.add_lab("1_3","LC","11/11/2021")
        self.serv.asignare(1,"1_3")
        self.serv.asignare(2,"1_3")
        self.serv.add_nota(1,"1_2",3)
        self.serv.add_nota(2,"1_3",2)
        self.serv.add_nota(1,"1_3",4)
        all=self.serv.get_all_note_sort_name()
        self.assertEqual(all[0].get_student(),2)
    
    def test_get_all_note_sort_nota(self):
        self.serv_s.add_student("A B",217)
        self.serv_l.add_lab("1_3","LC","11/11/2021")
        self.serv.asignare(1,"1_3")
        self.serv.asignare(2,"1_3")
        self.serv.add_nota(1,"1_2",8.7)
        self.serv.add_nota(2,"1_3",9.6)
        all=self.serv.get_all_note_sort_nota()
        self.assertEqual(all[0].get_student(),2)
    
    def test_get_all_note_less_5(self):
        self.serv_s.add_student("A B",217)
        self.serv_l.add_lab("1_3","LC","11/11/2021")
        self.serv.asignare(1,"1_3")
        self.serv.asignare(2,"1_3")
        self.serv.add_nota(1,"1_2",6)
        self.serv.add_nota(2,"1_3",10)
        all=self.serv.get_all_note_less_5()
        self.assertEqual(all,[])
    
    def test_get_all_note_top3(self):
        self.serv_s.add_student("A B",217)
        self.serv_l.add_lab("1_3","LC","11/11/2021")
        self.serv.asignare(2,"1_2")
        self.serv.asignare(1,"1_3")
        self.assertEqual(self.serv.get_all_note_top3()[0][0],2)

