import unittest
from domain.entities import lab_prb, notare, student
from domain.validators import ValidatorException, validator_lab, validator_notare, validator_student

class testcase_validator_student(unittest.TestCase):
    def setUp(self):
        self.s=student("","")
        self.val=validator_student()
    
    def tearDown(self):
        student.newid=1
    
    def test_validator_student(self):
        self.assertRaises(ValidatorException,self.val.student_validate,self.s)

class testcase_validator_lab(unittest.TestCase):
    def setUp(self):
        self.l=lab_prb("","","")
        self.val=validator_lab()
    
    def tearDown(self):
        pass
    
    def test_validator_lab(self):
        self.assertRaises(ValidatorException,self.val.lab_validate,self.l)

class testcase_validator_notare(unittest.TestCase):
    def setUp(self):
        self.n=notare("","")
        self.val=validator_notare()
    
    def tearDown(self):
        pass
    
    def test_validator_notare(self):
        self.assertRaises(ValidatorException,self.val.notare_validate,self.n,False,False)