import unittest
from utils.sorts import sort_selection, sort_shake

class testcase_sorts(unittest.TestCase):
    def setUp(self):
        self.l=[9,2,31,4,2,6]
    
    def tearDown(self):
        pass

    def test_sort_selection(self):
        self.assertEqual(sort_selection(self.l),[2,2,4,6,9,31])
        self.assertEqual(sort_selection(self.l,reversed=True),[31,9,6,4,2,2])
        self.assertEqual(sort_selection(self.l,key=lambda x: x%3),[9,6,31,4,2,2])
        self.assertEqual(sort_selection(self.l,cmp=lambda x,y:x-y),[2,2,4,6,9,31])
    
    def test_sort_shake(self):
        self.assertEqual(sort_shake(self.l),[2,2,4,6,9,31])
        self.assertEqual(sort_shake(self.l,reversed=True),[31,9,6,4,2,2])
        self.assertEqual(sort_shake(self.l,key=lambda x: x%3),[9,6,31,4,2,2])
    