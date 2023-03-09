from utils.conditions import condition_desc
#modulul functionalitatii de rapoarte
from utils.cheltuiala import get_date, get_cost, get_desc,create_expense

def raport_totalcost_X(database:list,condition:str):

    #functia calculeaza din lista suma totala a costurilor pentru o conditie data
    #functia primeste lista pe care se calculeaza si conditia de tip string
    #functia returneaza costul total dupa o conditie data
    total=0
    for el in database:
        if eval(condition):
            total=total+el.cost
    return round(total,2)

def raport_maxcost_date(database:list):

    #functia calculeaza din lista zilele unde suma este maxima
    #functia primeste lista de unde se calculeaza
    #functia returneaza lista cu zilele in care suma e maxima

    days=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    for el in database:
        days[get_date(el)]+=get_cost(el)
    maxi=-1
    dmax=[]
    for i,el in enumerate(days):
        if el>maxi:
            maxi=el
            dmax=[i]
        elif el==maxi:
            dmax.append(i)
    return dmax

def raport_sort_expenses_X(database:list,X:str):
    
    #functia sorteaza elementele de tip expense dupa atributul introdus prin X
    #functia primeste lista de sortat si X care reprezinta dupa ce se sorteaza
    #functia returneaza lista sortata

    if X=='desc':
        database.sort(key=lambda expense: get_desc(expense))
    elif X=='cost':
        database.sort(key=lambda expense: get_cost(expense))
    elif X=='date':
        database.sort(key=lambda expense: get_date(expense))
    return database

def raport_totalcost_desc(database:list,desc:str):

    return raport_totalcost_X(database,condition_desc(desc))

def test_raport_totalcost_desc():

    #functia de testare pentru functia raport_totalcost_desc
    l=[]
    l.append(create_expense(1,11,"Mancare"))
    l.append(create_expense(2,30,"Mancare"))
    assert raport_totalcost_X(l,condition_desc("Mancare"))==41
    l=[]
    l.append(create_expense(1,11,"Mancare"))
    l.append(create_expense(2,30.5,"Mancare"))
    assert raport_totalcost_X(l,condition_desc("Mancare"))==41.5

def test_raport_maxcost_date():
    #functie de test pentru functia raport_maxcost_date
    l=[]
    l.append(create_expense(1,11,"Mancare"))
    l.append(create_expense(2,30,"Mancare"))
    assert raport_maxcost_date(l)==[2]
    l=[]
    l.append(create_expense(1,11,"Mancare"))
    l.append(create_expense(2,11,"Mancare"))
    assert raport_maxcost_date(l)==[1,2]

def test_raport_sort_expenses_desc():
    #functie de test pentru functia raport_sort_expenses_X unde X este desc
    l=[]
    l.append(create_expense(1,11,"Mancare"))
    l.append(create_expense(2,30,"Bautura"))
    l2=[]
    l2.append(create_expense(2,30,"Bautura"))
    l2.append(create_expense(1,11,"Mancare"))
    assert raport_sort_expenses_X(l,'desc')==l2
    l=[]
    l.append(create_expense(1,11,"Mancare"))
    l.append(create_expense(2,11,"Taxi"))
    assert raport_sort_expenses_X(l,'desc')==l

test_raport_totalcost_desc()
test_raport_maxcost_date()
test_raport_sort_expenses_desc()