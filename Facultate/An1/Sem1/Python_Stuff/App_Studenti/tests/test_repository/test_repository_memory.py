import unittest
from domain.entities import lab_prb, notare, student
from repository.memory import memory_lab, memory_nota, memory_student

class testcase_memory_student(unittest.TestCase):
    def setUp(self):
        self.s=student("X Y",215)
        self.repo=memory_student()
        self.repo.add_student(self.s)
    
    def tearDown(self):
        student.newid=1
    
    def test_add_student(self):
        all=self.repo.get_all_students()
        self.assertEqual(all[0],self.s)
    
    def test_remove_student(self):
        self.repo.remove_student(1)
        all=self.repo.get_all_students()
        self.assertEqual(all,[])
    
    def test_modify_student(self):
        s2=student("Y X",215)
        s2.set_id(1)
        self.repo.modify_student(s2)
        all=self.repo.get_all_students()
        self.assertEqual(all[0],s2)
    
    def test_get_one_student(self):
        r=self.repo.get_one_student(1,0)
        self.assertEqual(r,self.s)

class testcase_memory_lab(unittest.TestCase):
    def setUp(self):
        self.l=lab_prb("6_9","FP","08/11/2021")
        self.repo=memory_lab()
        self.repo.add_lab(self.l)
    
    def tearDown(self):
        pass
    
    def test_add_lab(self):
        all=self.repo.get_all_labs()
        self.assertEqual(all[0],self.l)
    
    def test_remove_lab(self):
        self.repo.remove_lab("6_9")
        all=self.repo.get_all_labs()
        self.assertEqual(all,[])
    
    def test_modify_lab(self):
        l2=lab_prb("1_2","FP","11/11/2011")
        l2.set_nrlb_nrprb("6_9")
        self.repo.modify_lab(l2)
        all=self.repo.get_all_labs()
        self.assertEqual(all[0],l2)
    
    def test_get_one_lab(self):
        r=self.repo.get_one_lab("6_9",0)
        self.assertEqual(r,self.l)

class testcase_memory_notare(unittest.TestCase):
    def setUp(self):
        self.n=notare(1,"1_2")
        self.repo=memory_nota()
        self.repo.asignare(self.n)
    
    def tearDown(self):
        pass
    
    def test_asignare(self):
        all=self.repo.get_all_note()
        self.assertEqual(all[0],self.n)
    
    def test_add_nota(self):
        all=self.repo.get_all_note()
        self.assertEqual(all[0].get_nota(),None)
        self.repo.add_nota(1,"1_2",10)
        all=self.repo.get_all_note()
        self.assertEqual(all[0].get_nota(),10)
    
    def test_remove_asg(self):
        self.repo.remove_asg(1,"1_2")
        all=self.repo.get_all_note()
        self.assertEqual(all,[])
