#modulul functionalitatii de filtrare
from utils.conditions import condition_desc, condition_lesscost
from utils.cheltuiala import create_expense

def filter_expenses_X(database:list,condition:str):
    
    #functia filtreaza din lista toate elementele de tip expense in functie de o conditie data
    #functia primeste lista din care se sterge si conditia dupa care se sterge (conditia este de tip string)
    #functia returneaza noua lista
    db=[]
    for el in database:
        if not eval(condition):
            db.append(el)    
    return db

def filter_expenses_desc(database:list,desc:str):

    return filter_expenses_X(database,condition_desc(desc))

def filter_expenses_lesscost(database:list,cost:str):

    return filter_expenses_X(database,condition_lesscost(cost))

def test_filter_lesscost():

    #functie de testare pentru filter_expenses_X unde X este mai mic decat un cost dat
    l=[]
    l.append(create_expense(1,11,"Mancare"))
    l.append(create_expense(1,30,"Bautura"))
    l2=[]
    l2.append(create_expense(1,30,"Bautura"))
    assert filter_expenses_X(l,condition_lesscost('29'))==l2
    assert filter_expenses_X(l,condition_lesscost('100'))==[]

def test_filter_desc():
    
    #functie de testare pentru filter_expenses_X unde X este desc
    l=[]
    l.append(create_expense(1,11,"Mancare"))
    l.append(create_expense(1,30,"Bautura"))
    l2=[]
    l2.append(create_expense(1,30,"Bautura"))
    assert filter_expenses_X(l,condition_desc('Mancare'))==l2
    l2=[]
    l2.append(create_expense(1,11,"Mancare"))
    assert filter_expenses_X(l,condition_desc('Bautura'))==l2

test_filter_lesscost()
test_filter_desc()
