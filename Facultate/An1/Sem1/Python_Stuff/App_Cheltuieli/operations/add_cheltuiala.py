#modulul functionalitatii de adaugare
from utils.cheltuiala import set_cost, set_date, set_desc, create_expense

def add_expense(database:list,date:int,cost:float,desc:str):

    #functia adauga in lista un element de tip expense
    #functia primeste lista in care se adauga elementul si fiecare atribut al elementului respectiv data, costul si descrierea
    #functia returneaza lista modificata

    database.append(create_expense(date,cost,desc))
    return database

def change_expense(database:list,nr,new_date:int,new_cost:float,new_desc:str):
    
    #functia schimba un elementul de pe pozitia nr de tip expense din lista
    #functia primeste lista in care se schimba elementul, pozitia elementului si noile atributele ale lui
    #functia returneaza lista modificata
    
    database[nr]=set_date(database[nr],new_date)
    database[nr]=set_cost(database[nr],new_cost)
    database[nr]=set_desc(database[nr],new_desc)
    return database

def test_add_expense():
    
    #functie care testeaza functia add_expenses
    l=[]
    l.append(create_expense(1,11,"Mancare"))
    assert add_expense([],1,11,"Mancare")==l
    l.append(create_expense(2,88.5,"Intretinere"))
    l2=[]
    l2.append(create_expense(1,11,"Mancare"))
    assert add_expense(l2 , 2, 88.5, "Intretinere")==l

def test_change_expense():
    
    #functie de teste pentru testarea functiei change_expenses
    l=[]
    l.append(create_expense(1,11,"Manare"))
    l2=[]
    l2.append(create_expense(1,70,"Bautura"))
    assert change_expense(l,0,1,70,"Bautura")==l2

    l=[]
    l.append(create_expense(1,11,"Mancare"))
    l.append(create_expense(2,88.5,"Intretinere"))
    l2=[]
    l2.append(create_expense(1,11,"Mancare"))
    l2.append(create_expense(2,90,"Intretinere"))
    assert change_expense(l,1, 2, 90, "Intretinere")==l2

test_add_expense()
test_change_expense()