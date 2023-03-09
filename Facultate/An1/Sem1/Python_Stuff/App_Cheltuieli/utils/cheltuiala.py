#modulul care contine tipul de date folosit
from dataclasses import dataclass

@dataclass
class expense:
    date:int
    cost:float
    desc:str

class CheltuialaError(Exception):
    pass

def get_date(cheltuiala):
    return cheltuiala.date

def get_cost(cheltuiala):
    return cheltuiala.cost

def get_desc(cheltuiala):
    return cheltuiala.desc

def set_date(cheltuiala:expense,date:int):
    cheltuiala.date=date
    return cheltuiala

def set_cost(cheltuiala:expense,cost:float):
    cheltuiala.cost=cost
    return cheltuiala

def set_desc(cheltuiala:expense,desc:str):
    cheltuiala.desc=desc
    return cheltuiala

def create_expense(date:int,cost:float,desc:str):
    return expense(date=date,cost=cost,desc=desc)

def validate_expense(**kwargs):

    #functie care primeste argumente optionale pentru a valida inputul utilizatorului
    date = kwargs.get('date',None)
    cost = kwargs.get('cost',None)
    desc = kwargs.get('desc',None)
    fmdate = kwargs.get('fmdate',None)
    todate = kwargs.get('fmdate',None)

    accepted=("Mancare","Chirie","Telefon","Taxi","Intretinere","Imbracaminte","Altele")
    errors=[]
    if((date != None) and (int(date)>31 or int(date)<1)):
        errors.append("Data trebuie sa fie una calendaristica")
    if((cost != None) and (float(cost)<0)):
        errors.append("Costul nu trebuie sa fie negativ")
    if((desc != None) and (desc not in accepted)):
        errors.append("Cheltuiala nu se incadreaza in cele acceptate")
    if((fmdate != None and todate != None) and (fmdate>todate or fmdate>31 or todate>31 or fmdate<1 or todate<1)):
        errors.append("Interval de date calendaristice incorect")


    if len(errors) > 0:
        errors='\n'.join(errors)
        raise CheltuialaError(errors)
    
def test_validate_expense():

    try:
        validate_expense(date='-1')
    except CheltuialaError as ve:
        assert str(ve)=="Data trebuie sa fie una calendaristica"
    
    try:
        validate_expense(cost='-1')
    except CheltuialaError as ve:
        assert str(ve)=="Costul nu trebuie sa fie negativ"
        
    try:
        validate_expense(desc='-1')
    except CheltuialaError as ve:
        assert str(ve)=="Cheltuiala nu se incadreaza in cele acceptate"

test_validate_expense()

