#modulul de interactionare cu utilizatorul
from operations.add_cheltuiala import add_expense, change_expense
from operations.remove_cheltuiala import remove_expenses_date, remove_expenses_fmdate_todate, remove_expenses_desc
from operations.find_cheltuiala import find_expenses_grtcost, find_expenses_lessdate_and_lesscost, find_expenses_desc, find_expenses_cost
from operations.filter_cheltuiala import filter_expenses_desc, filter_expenses_lesscost
from operations.raport_cheltuiala import raport_totalcost_desc, raport_maxcost_date, raport_sort_expenses_X
from utils.cheltuiala import get_date, get_cost, get_desc, validate_expense, CheltuialaError
from operations.undo_cheltuiala import undo, make_backup

def printall(database:list):

    #functie care afiseaza pe ecran toate elementele din lista cu cheltuieli
    if not database:
        print("Nu exista cheltuieli")
    else:
        for i,el in enumerate(database):
            print("Cheltuiala cu numarul",i+1,": Date -",get_date(el),"Cost -",get_cost(el),"Type -",get_desc(el))
    print()

def ui(state):
    #functie care printeaza interfata

    if(state=='-1'):
        print("Puteti introduce si o comanda")
        print("1: Afiseaza toate cheltuielile")
        print("2: Intrati in sectiunea de modificari")
        print("3: Intrati in sectiunea de stergeri")
        print("4: Intrati in sectiunea de cautari")
        print("5: Intrati in sectiunea de rapoarte")
        print("6: Intrati in sectiunea de filtrare")
        print("7: Intrati in sectiunea de undo")
        print("0: Iesiti din aplicatie")
        print()
    elif(state=='add'):
        print("1: Adauga o noua cheltuiala")
        print("2: Modifica o cheltuiala")
        print("0: Iesire la meniul principal")
        print()
    elif(state=='remove'):
        print("1: Sterge toate cheltuielile pentru o zi data")
        print("2: Sterge toate cheltuielile pentru un interval de timp")
        print("3: Sterge toate cheltuielile de un anumit tip")
        print("0: Iesire la meniul principal")
        print()
    elif(state=='find'):
        print("1: Afiseaza toate cheltuielile mai mari decat o suma data")
        print("2: Afiseaza toate cheltuielile efectuate inainte de o zi data și mai mici decat o suma data")
        print("3: Afiseaza toate cheltuielile de un anumit tip")
        print("0: Iesire la meniul principal")
        print()
    elif(state=='raport'):
        print("1: Afiseaza suma totala pentru un anumit tip de cheltuiala")
        print("2: Afiseaza zilele in care suma cheltuita este maxima")
        print("3: Afiseaza cheltuielile care au o anumita suma")
        print("4: Afiseaza cheltuielile sortare dupa tip")
        print("0: Iesire la meniul principal")
        print()
    elif(state=='filtrare'):
        print("1: Elimina toate cheltuielile de un anumit tip")
        print("2: Elimina toate cheltuielile mai mici decat o suma data")
        print("0: Iesire la meniul principal")
    elif(state=='undo'):
        print("1: Undo ultima operatie facuta")
        print("0: Iesire la meniul principal")

def option_add(database:list,backup:list):

    #functie pentru sectiunea modificari
    while True:
        ui('add')
        n=input("Alegeti optiunea: ")
        if(n=='0'):
            return database, backup
        elif(n=='1'):

            try:
                date=int(input("Introduceti data cheluielii "))
                cost=float(input("Introduceti costul cheltuielii "))
                desc=input("Introduceti descrierea cheltuielii ")
                validate_expense(date=date,cost=cost,desc=desc)
                backup=make_backup(database,backup)
                database=add_expense(database,date,cost,desc)
            except ValueError:
                print('\033[91m'+"Eroare, date de tip gresit"+'\033[0m')
            except CheltuialaError as ce:
                print('\033[91m'+str(ce)+'\033[0m')

        elif(n=='2'):

            try:
                nr=int(input("Introduceti numarul cheluielii pe care vreti sa o modificati "))
                date=int(input("Introduceti noua data a cheluielii "))
                cost=float(input("Introduceti noul costul al cheltuielii "))
                desc=input("Introduceti noua descrierea a cheltuielii ")
                validate_expense(date=date,cost=cost)
                backup=make_backup(database,backup)
                database=change_expense(database,nr-1,date,cost,desc)
            except ValueError:
                print('\033[91m'+"Eroare, date de tip gresit"+'\033[0m')
            except CheltuialaError as ce:
                print('\033[91m'+str(ce)+'\033[0m')
            except IndexError:
                print('\033[91m'+"Nu se afla in baza de date"+'\033[0m')


        else:
            print('\033[91m'+"Nu exista optiunea"+'\033[0m')
        print()
            
def option_remove(database:list,backup:list):
    #functie pentru sectia stergeri
    while True:
        ui('remove')
        n=input("Alegeti optiunea: ")
        if(n=='0'):
            return database, backup
        elif(n=='1'):
            
            try:
                date=input("Introduceti data ")
                validate_expense(date=date)
                backup=make_backup(database,backup)
                database=remove_expenses_date(database,date)
            except ValueError:
                print('\033[91m'+"Eroare, date de tip gresit"+'\033[0m')
            except CheltuialaError as ce:
                print('\033[91m'+str(ce)+'\033[0m')

        elif(n=='2'):

            try:
                fmdate=int(input("Introduceti data de inceput "))
                todate=int(input("Introduceti data de sfarsit "))
                validate_expense(fmdate=fmdate,todate=todate)
                backup=make_backup(database,backup)
                database=remove_expenses_fmdate_todate(database,fmdate,todate)
            except ValueError:
                print('\033[91m'+"Eroare, date de tip gresit"+'\033[0m')
            except CheltuialaError as ce:
                print('\033[91m'+str(ce)+'\033[0m')
            except KeyError:
                print("Eroare, indici gresiti")

        elif(n=='3'):

            try:
                desc=input("Introduceti tipul ")
                validate_expense(desc=desc)
                backup=make_backup(database,backup)
                database=remove_expenses_desc(database,desc)
            except ValueError:
                print('\033[91m'+"Eroare, date de tip gresit"+'\033[0m')
            except CheltuialaError as ce:
                print('\033[91m'+str(ce)+'\033[0m')

        else:
            print('\033[91m'+"Nu exista optiunea"+'\033[0m')
        print()

def option_find(database:list):
    #functie pentru sectia cautari
    while True:
        ui('find')
        n=input("Alegeti optiunea: ")
        if(n=='0'):
            return database
        elif(n=='1'):

            try:
                cost=input("Introduceti suma: ")
                validate_expense(cost=cost)
                printall(find_expenses_grtcost(database,cost))
            except ValueError:
                print('\033[91m'+"Eroare, date de tip gresit"+'\033[0m')
            except CheltuialaError as ce:
                print('\033[91m'+str(ce)+'\033[0m')  

        elif(n=='2'):

            try:
                date=input("Introduceti data: ")
                cost=input("Introduceti suma: ")
                validate_expense(date=date,cost=cost)
                printall(find_expenses_lessdate_and_lesscost(database,date,cost))
            except ValueError:
                print('\033[91m'+"Eroare, date de tip gresit"+'\033[0m')
            except CheltuialaError as ce:
                print('\033[91m'+str(ce)+'\033[0m')

        elif(n=='3'):

            try:
                desc=input("Introduceti tipul ")
                validate_expense(desc=desc)
                printall(find_expenses_desc(database,desc))
            except ValueError:
                print('\033[91m'+"Eroare, date de tip gresit"+'\033[0m')
            except CheltuialaError as ce:
                print('\033[91m'+str(ce)+'\033[0m')
        else:
            print('\033[91m'+"Nu exista optiunea"+'\033[0m')
        print()

def option_filtrare(database:list,backup:list):
    #functie pentru sectia de filtrare
    while True:
        ui("filtrare")
        n=input("Alegeti optiunea: ")
        if(n=='0'):
            return database, backup
        elif(n=='1'):

            try: 
                desc=input("Introduceti tipul ")
                validate_expense(desc=desc)
                backup=make_backup(database,backup)
                database=filter_expenses_desc(database,desc)
            except ValueError:
                print('\033[91m'+"Eroare, date de tip gresit"+'\033[0m')
            except CheltuialaError as ce:
                print('\033[91m'+str(ce)+'\033[0m')

        elif(n=='2'):

            try:
                cost=input("Introduceti suma ")
                validate_expense(cost=cost)
                backup=make_backup(database,backup)
                database=filter_expenses_lesscost(database, cost)
            except ValueError:
                print('\033[91m'+"Eroare, date de tip gresit"+'\033[0m')
            except CheltuialaError as ce:
                print('\033[91m'+str(ce)+'\033[0m')
        else:
            print('\033[91m'+"Nu exista optiunea"+'\033[0m') 
        print()

def option_raport(database:list):
    #functie pentru sectia de rapoarte
    while True:
        ui("raport")
        n=input("Alegeti optiunea: ")
        if(n=='0'):
            return database
        elif(n=='1'):
            try:
                desc=input("Introduceti tipul ")
                validate_expense(desc=desc)
                print("Suma totala pentru",desc.upper(),"este",raport_totalcost_desc(database,desc))
            except CheltuialaError as ce:
                print('\033[91m'+str(ce)+'\033[0m')
        elif(n=='2'):
            days=raport_maxcost_date(database)
            if len(days)==1:
                print("Ziua in care suma este maxima este:", days[0])
            else:
                print("Zilele in care suma este maxima sunt:", *days)
        elif(n=='3'):
            try:
                cost=input("Introduceti suma ")
                validate_expense(cost=cost)
                printall(find_expenses_cost(database,cost))
            except:
                print("Eroare, date de tip gresit")
        elif(n=='4'):
            printall(raport_sort_expenses_X(database,'desc'))
        else:
            print('\033[91m'+"Nu exista optiunea"+'\033[0m')
        print()

def option_undo(database:list,backup:list):
    #functia pentru sectia de undo
    while True:
        ui("undo")
        n=input("Alegeti optiunea: ")
        if(n=='0'):
            return database, backup
        elif(n=='1'):
            try:
                database,backup=undo(database,backup)
                print("S-a facut operatia de UNDO")
            except IndexError:
                print('\033[91m'+"Nu se mai poate face undo."+'\033[0m')
        else:
            print('\033[91m'+"Nu exista optiunea"+'\033[0m') 
        print()

def option_cmd(cmd:str, database:list, backup:list):
    #functia de apelare comanda tip terminal
    cmd=cmd.split()
    if cmd[0]=='adauga':
        try:
            validate_expense(date=cmd[1],cost=cmd[2],desc=cmd[3])
            backup=make_backup(database,backup)
            add_expense(database,cmd[1],cmd[2],cmd[3])
        except ValueError:
            print('\033[91m'+"Eroare, date de tip gresit"+'\033[0m')
        except CheltuialaError as ce:
            print('\033[91m'+str(ce)+'\033[0m')

    elif cmd[0]=='sterge':
        try:
            validate_expense(date=cmd[1])
            backup=make_backup(database,backup)
            remove_expenses_date(database,cmd[1])
        except ValueError:
            print('\033[91m'+"Eroare, date de tip gresit"+'\033[0m')
        except CheltuialaError as ce:
            print('\033[91m'+str(ce)+'\033[0m')

    elif cmd[0]=='cauta':
        try:
            validate_expense(desc=cmd[1])
            backup=make_backup(database,backup)
            find_expenses_desc(database,cmd[1])
        except ValueError:
            print('\033[91m'+"Eroare, date de tip gresit"+'\033[0m')
        except CheltuialaError as ce:
            print('\033[91m'+str(ce)+'\033[0m')

    elif cmd[0]=='raport':
        if cmd[1]=='sortare':
            try:
                printall(raport_sort_expenses_X(database,"desc"))
            except:
                print('\033[91m'+"Eroare"+'\033[0m')
                
    elif cmd[0]=='undo':
        try:
            database,backup=undo(database,backup)
            print("S-a facut operatia de UNDO")
        except IndexError:
            print('\033[91m'+"Nu se mai poate face undo."+'\033[0m')

    else:
        print('\033[91m'+"Nu exista optiunea"+'\033[0m')
    print()
    return database, backup

def option_main(database:list,backup:list):
    #functia pentru meniul principal
    while True:
        ui('-1')
        n=input("Alegeti optiunea: ")
        if(n=='0'):
            return
        elif(n=='1'):
            printall(database)
        elif(n=='2'):
            database,backup=option_add(database,backup)
        elif(n=='3'):
            database,backup=option_remove(database,backup)
        elif(n=='4'):
            database=option_find(database)
        elif(n=='5'):
            database=option_raport(database)
        elif(n=='6'):
            database,backup=option_filtrare(database,backup)
        elif(n=='7'):
            database,backup=option_undo(database,backup)
        else:
            database,backup=option_cmd(n,database,backup)
