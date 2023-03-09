#
from repository.repo import repo_pictura
from services.services import services_pictura


def test_get_all_nume_sort_an():
    repo=repo_pictura("tests/test_data.txt")
    serv=services_pictura(repo)
    l=serv.get_all_nume_sort_an("Lisa")
    assert l[0].get_id()==21
    assert l[1].get_id()==9

    try:
        l=serv.get_all_nume_sort_an("LLLLL")
        assert False
    except:
        assert True
        
def test_get_cel_mai_recent():
    repo=repo_pictura("tests/test_data.txt")
    serv=services_pictura(repo)
    l=serv.get_cel_mai_recent()
    assert l[0][1]==1889
    assert l[1][1]==1762

test_get_all_nume_sort_an()
test_get_cel_mai_recent()
