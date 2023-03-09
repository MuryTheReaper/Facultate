#modulul functionalitatii de undo

def make_backup(database:list,backup:list,):
    #functia adauga o noua versiune a listei database in lista de liste backup pentru pastrare
    #functia primeste o lista de liste backup in care se retin liste database
    #functia returneaza lista de liste backup

    backup.append(database)
    return backup

def remove_backup(backup:list):
    #functia sterge cel mai recent element din lista de liste backup
    #functia primeste lista de liste backup
    #functia returneaza lista de liste fara cel mai recent element

    del backup[-1]
    return backup

def undo(database:list,backup:list,):
    #functia face operatia de undo a listei database 
    #functia primeste lista de liste backup si lista database
    #functia returneaza lista database inainte de ultima operatie
    
    database=backup[-1]
    backup=remove_backup(backup)
    return database, backup

def test_make_backup():
    #functia de test pentru functia make_backup
    l=[1,2,3]
    bk=[[1],[1,2]]
    r=[[1],[1,2],[1,2,3]]
    assert make_backup(l,bk)==r

def test_remove_backup():
    #functia de teste penrtu functia remove_backup
    bk=[[1],[1,2]]
    r=[[1]]
    assert remove_backup(bk)==r

def test_undo():
    #functia de test pentru functia de undo
    l=[1,2,3,4]
    bk=[[1],[1,2],[1,2,3]]
    r=[1,2,3]
    rbk=[[1],[1,2]]
    l,bk=undo(l,bk)
    assert r==l
    assert rbk==bk

test_make_backup()
test_remove_backup()
test_undo()



