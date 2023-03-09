#modul pentru testing/demo
from operations.add_cheltuiala import add_expense

def generate_database(database:list):
    #functie de generare o lista de cheltuieli pentru teste manuale

    add_expense(database,1,12.3,"Mancare")
    add_expense(database,2,21,"Mancare")
    add_expense(database,2,11,"Telefon")
    add_expense(database,2,5.5,"Taxi")
    add_expense(database,10,17.9,"Mancare")
    add_expense(database,11,188.2,"Chirie")
    add_expense(database,13,99.9,"Imbracaminte")
    add_expense(database,14,21,"Mancare")
    add_expense(database,14,11,"Telefon")
    return database
