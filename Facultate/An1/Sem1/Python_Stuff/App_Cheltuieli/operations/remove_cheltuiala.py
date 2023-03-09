#modulul functionalitatii de stergere
from utils.conditions import condition_date, condition_desc
from utils.cheltuiala import create_expense

def remove_expenses_fmdate_todate(database:list,fmdate:int,todate:int):
    
    #functia sterge toate elementele de tip expense din lista care are atributul date cuprins intre fmdate si todate
    #functia primeste lista din care se sterge si inceputul si sfarsitul intervalului de sters
    #functia returneaza noua lista

    for i in range(fmdate,todate+1):
        database=remove_expenses_X(database,condition_date(str(i)))
    return database

def remove_expenses_X(database:list,condition:str):
    
    #functia sterge din lista toate elementele de tip expense in functie de o conditie data
    #functia primeste lista din care se sterge si conditia dupa care se sterge (conditia este de tip string)
    #functia returneaza noua lista
    db=[]
    for el in database:
        if not eval(condition):
            db.append(el)    
    return db

def remove_expenses_date(database:list,date:str):
    
    return remove_expenses_X(database,condition_date(date))

def remove_expenses_desc(database:list,desc:str):

    return remove_expenses_X(database,condition_desc(desc))

def test_remove_expenses_date():

    #functie de teste pentru testarea functiei remove_expenses_X unde X este date
    l=[]
    l.append(create_expense(1,11,"Mancare"))
    assert remove_expenses_X(l,condition_date('1'))==[]
    l=[]
    l.append(create_expense(1,11,"Mancare"))
    l.append(create_expense(2,11,"Mancare"))
    l2=[]
    l2.append(create_expense(2,11,"Mancare"))
    assert remove_expenses_X(l,condition_date('1'))==l2

def test_remove_expenses_fmdate_todate():

    #functie de teste pentru testarea functiei remove_expenses_fmdate_todate
    l=[]
    l.append(create_expense(1,11,"Mancare"))
    l.append(create_expense(2,60,"Bautura"))
    assert remove_expenses_fmdate_todate(l,1,2)==[]

def test_remove_expenses_desc():
    
    #functia de teste pentru testarea functiei remove_expenses_X unde X este desc
    l=[]
    l.append(create_expense(1,11,"Mancare"))
    l.append(create_expense(2,11,"Bautura"))
    l2=[]
    l2.append(create_expense(2,11,"Bautura"))
    assert remove_expenses_X(l,condition_desc("Mancare"))==l2

test_remove_expenses_date()
test_remove_expenses_fmdate_todate()
test_remove_expenses_desc()
   