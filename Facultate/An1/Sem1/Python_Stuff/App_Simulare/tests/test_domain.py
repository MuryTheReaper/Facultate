#modulul pentru testele functiilor din domain

from domain.entities import pictura


def test_pictura():
    p=pictura(2,"Mona Lisa","Leonardo da Vinci",1491)
    assert p.get_id()==2
    assert p.get_nume()=="Mona Lisa"
    assert p.get_nume_autor()=="Leonardo da Vinci"
    assert p.get_an()==1491

test_pictura()