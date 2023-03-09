#modulul pentru testele functiilor din repo

from repository.repo import repo_pictura


def test_repo():
    repo=repo_pictura("tests/test_data.txt")
    l=repo.get_all_pictura()
    assert l[0].get_id()==9
    assert l[0].get_nume()=="Mona Lisa"
    assert l[0].get_nume_autor()=="Leonardo da Vinci"
    assert l[0].get_an()==1519

test_repo()