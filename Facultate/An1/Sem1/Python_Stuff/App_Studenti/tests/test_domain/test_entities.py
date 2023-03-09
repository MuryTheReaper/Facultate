import unittest

from domain.entities import lab_prb, notare, student

class testcase_student(unittest.TestCase):
    def setUp(self):
        self.s1=student("X Y",215)
        self.s2=student("Y X",215)
    
    def tearDown(self):
        student.newid=1
    
    def test_student(self):
        self.assertEqual(self.s1.get_id(),1,"Student ID")
        self.assertEqual(self.s1.get_nume(),"X Y", "Student nume")
        self.assertEqual(self.s1.get_grupa(),215,"Student grupa")
        self.assertEqual(self.s2.get_id(),2,"Student auto ID")

class testcase_lab(unittest.TestCase):
    def setUp(self):
        self.l=lab_prb("1_1","ASC","21/01/2019")

    def tearDown(self):
        pass
    
    def test_lab(self):
        self.assertEqual(self.l.get_nrlb_nrprb(),"1_1","Lab ID")
        self.assertEqual(self.l.get_desc(),"ASC", "Lab desc")
        self.assertEqual(self.l.get_deadline(),"21/01/2019","Lab deadline")

class testcase_notare(unittest.TestCase):
    def setUp(self):
        self.n1=notare(1,"1_2")
        self.n2=notare(2,"2_1",10)
    
    def tearDown(self):
        pass
    
    def test_notare(self):
        self.assertEqual(self.n1.get_student(),1,"Notare student ID")
        self.assertEqual(self.n1.get_lab(),"1_2", "Notare lab ID")
        self.assertEqual(self.n2.get_nota(),10,"Notare nota")

