#modul de creare conditii pentru functiile din pachetul operations
from utils.cheltuiala import create_expense


def condition_date(date:str):

    #functia creeaza conditia daca atributul date al cheltuielei este egal cu parametrul de intrare
    #primeste valoare cu care trebuie sa fie egal atriburul date
    #returneaza conditia logica corespunzatoare de tip string
    x=create_expense(0,0,"")
    x=list(vars(x).keys())[0]
    condition="el."+x+"=="+date
    return condition

def condition_cost(cost:str):

    #functia creeaza conditia daca atributul cost al cheltuielei este egal cu parametrul de intrare
    #primeste valoare cu care trebuie sa fie egal atriburul cost
    #returneaza conditia logica corespunzatoare de tip string

    x=create_expense(0,0,"")
    x=list(vars(x).keys())[1]
    condition="el."+x+"=="+cost
    return condition

def condition_grtcost(grtcost:str):

    #functia creeaza conditia daca atributul cost al cheltuielei este mai mare decat parametrul de intrare
    #primeste valoare dupa care se compara atriburul cost
    #returneaza conditia logica corespunzatoare de tip string

    x=create_expense(0,0,"")
    x=list(vars(x).keys())[1]
    condition="el."+x+">"+grtcost
    return condition

def condition_lesscost(lesscost:str):

    #functia creeaza conditia daca atributul cost al cheltuielei este mai mic decat parametrul de intrare
    #primeste valoare dupa care se compara atriburul cost
    #returneaza conditia logica corespunzatoare de tip string
    
    x=create_expense(0,0,"")
    x=list(vars(x).keys())[1]
    condition="el."+x+"<"+lesscost
    return condition

def condition_desc(desc:str):

    #functia creeaza conditia daca atributul desc al cheltuielei este egal cu parametrul de intrare
    #primeste valoare cu care trebuie sa fie egal atriburul desc
    #returneaza conditia logica corespunzatoare de tip string

    x=create_expense(0,0,"")
    x=list(vars(x).keys())[2]
    condition="el."+x+"=="+"\""+desc+"\""
    return condition

def condition_lessdate_and_lesscost(lessdate:str,lesscost:str):

    #functia creeaza conditia daca atributul date si cost al cheltuielei sunt mai mici decat parametrii de intrare
    #primeste valorile dupa care se compara atributele date si cost
    #returneaza conditia logica corespunzatoare de tip string

    x=create_expense(0,0,"")
    y=list(vars(x).keys())[0]
    x=list(vars(x).keys())[1]
    condition="el."+y+"<"+lessdate+" and el."+x+"<"+lesscost
    return condition

def test_condition_date():
    #functie care testeaza functia condition_date
    x=create_expense(0,0,"")
    x=list(vars(x).keys())[0]
    assert condition_date("1")=="el."+x+"==1"

def test_condition_cost():
    #functie care testeaza functia condition_cost
    x=create_expense(0,0,"")
    x=list(vars(x).keys())[1]
    assert condition_cost("1.2")=="el."+x+"==1.2"

def test_condition_grtcost():
    #functie care testeaza functia condition_grtcost
    x=create_expense(0,0,"")
    x=list(vars(x).keys())[1]
    assert condition_grtcost("1")=="el."+x+">1"

def test_condition_lesscost():
    #functie care testeaza functia condition_lesscost
    x=create_expense(0,0,"")
    x=list(vars(x).keys())[1]
    assert condition_lesscost("1")=="el."+x+"<1"

def test_condition_desc():
    #functie care testeaza functia condition_date
    x=create_expense(0,0,"")
    x=list(vars(x).keys())[2]
    assert condition_desc("Mancare")=="el."+x+"==\"Mancare\""

def test_condition_lessdate_and_lesscost():
    #functie care testeaza functia condition_date
    x=create_expense(0,0,"")
    y=list(vars(x).keys())[0]
    x=list(vars(x).keys())[1]
    assert condition_lessdate_and_lesscost("1","11")=="el."+y+"<1 and el."+x+"<11"

test_condition_date()
test_condition_cost()
test_condition_grtcost()
test_condition_lesscost()
test_condition_desc()
test_condition_lessdate_and_lesscost()

