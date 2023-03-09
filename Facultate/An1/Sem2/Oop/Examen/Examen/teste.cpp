#include "teste.h"
#include "assert.h"
#include "services.h"
// clang-format off



void test_read(){
  repository repo{"inputtest.txt"};
  services serv{repo};
  vector<melodie> list = serv.getAll();

  assert(list.size()==10);
  assert(list[0].getId()==1);
  assert(list[0].getTitlu()=="Titlu1");
  assert(list[0].getArtist()=="Artist1");
  assert(list[0].getRank()==9);
};

void test_sortByRank(){
  repository repo{"inputtest.txt"};
  services serv{repo};
  vector<melodie> list = serv.sortByRank();

  assert(list[0].getRank()==0);
}

void test_raport(){
  repository repo{"inputtest.txt"};
  services serv{repo};
  vector<melodie> list = serv.getAll();

  vector<std::pair<melodie, int>> rez{serv.raportSameRank()};

  assert(rez[1].second==1);
}

void test_find(){
  repository repo{"inputtest.txt"};
  services serv{repo};
  vector<melodie> list = serv.getAll();
  const int id =6;
  assert(serv.find(id,"Titlu6","Autor1",0).getId()==id);

  try{
  serv.find(-1,"","",0);assert(false);
  }catch(std::exception){
    assert(true);
  }

}

void test_nrRank(){
  repository repo{"inputtest.txt"};
  services serv{repo};
  vector<melodie> list = serv.getAll();

  assert(serv.nrRank()[0]==1);
}


void test_modify(){
  repository repo{"inputtest.txt"};
  services serv{repo};

  const int rank = 9;
  serv.modify(1,"Titlu1","Artist1", 0);
  serv.modify(1,"Titlu1","Artist1", rank);

  vector<melodie> list = serv.getAll();

  assert(list[0].getRank()==9);

}

void test_remove(){
  repository repo{"inputtestR.txt"};
  services serv{repo};
  vector<melodie> list = serv.getAll();

  int nr = int(list.size());

  const int rank = 9;
  serv.remove(1,"Titlu1","Artist1",rank);
  assert(serv.getAll().size()==nr-1);

  try{
    serv.remove(1,"Titlu1","Artist2",rank);assert(false);
  }
  catch(std::exception){
    assert(true);
  }

}
void test_all(){
  test_read();
  test_sortByRank();
  test_raport();
  test_find();
  test_nrRank();
  test_modify();
  test_remove();
}

// clang-format on
