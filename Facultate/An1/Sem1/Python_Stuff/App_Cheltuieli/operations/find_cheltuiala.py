#modulul functionalitatii de cautare
from utils.conditions import condition_cost, condition_grtcost, condition_lessdate_and_lesscost, condition_desc
from utils.cheltuiala import create_expense

def find_expenses_X(database:list,condition:str):

    #functia gaseste din lista toate elementele de tip expense in functie de o conditie data
    #functia primeste lista in care se cauta si conditia dupa care se cauta (conditia este de tip string)
    #returneaza o lista cu toate elementele gasite dupa conditia data

    db=[]
    for el in database:
        if eval(condition):
            db.append(el)
    return db

def find_expenses_grtcost(database:list,cost:str):

    return find_expenses_X(database,condition_grtcost(cost))

def find_expenses_lessdate_and_lesscost(database:list,date:str,cost:str):

    return find_expenses_X(database,condition_lessdate_and_lesscost(date,cost))

def find_expenses_desc(database:list,desc:str):

    return find_expenses_X(database,condition_desc(desc))

def find_expenses_cost(database:list,cost:str):

    return find_expenses_X(database,condition_cost(cost))

def test_find_expenses_grtcost():

    #functie de testare pentru testarea functiei find_trasactions_X unde X este mai mare decat un cost dat
    l=[]
    l.append(create_expense(1,11,"Mancare"))
    l.append(create_expense(1,30,"Bautura"))
    l2=[]
    l2.append(create_expense(1,30,"Bautura"))
    assert find_expenses_X(l,condition_grtcost('29'))==l2

def test_find_expenses_lessdate_and_lesscost():
    
    #functie de testare pentru testarea functiei find_trasactions_X unde X este mai mic decat un date si cost dat
    l=[]
    l.append(create_expense(1,61,"Mancare"))
    l.append(create_expense(1,62,"Mancare"))
    l.append(create_expense(1,11,"Bautura"))
    l2=[]
    l2.append(create_expense(1,11,"Bautura"))
    assert find_expenses_X(l,condition_lessdate_and_lesscost('12','60'))==l2

def test_find_expenses_desc():

    #functie de testare pentru testarea functiei find_expenses_X unde X este desc
    l=[]
    l.append(create_expense(1,11,"Mancare"))
    l.append(create_expense(1,11,"Bautura"))
    l2=[]
    l2.append(create_expense(1,11,"Mancare"))
    assert find_expenses_X(l,condition_desc("Mancare"))==l2

def test_find_expenses_cost():
    #functie de test pentru functia find_expenses_X unde X este cost
    l=[]
    l.append(create_expense(1,11,"Mancare"))
    l.append(create_expense(2,30,"Mancare"))
    l2=[]
    l2.append(create_expense(1,11,"Mancare"))
    assert find_expenses_X(l,condition_cost('11'))==l2
    l=[]
    l.append(create_expense(1,11,"Mancare"))
    l.append(create_expense(2,11,"Mancare"))
    assert find_expenses_X(l,condition_cost('11'))==l

test_find_expenses_grtcost()
test_find_expenses_lessdate_and_lesscost()
test_find_expenses_desc()
test_find_expenses_cost()