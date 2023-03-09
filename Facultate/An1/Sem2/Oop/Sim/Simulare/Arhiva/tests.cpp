#include "tests.h"
#include "assert.h"
#include "services.h"
// clang-format off



void test_read(){
  repository repo{"inputtest.txt"};
  services serv{repo};
  vector<device> list = serv.get_all();

  assert(list.size()==10);
  assert(list[2].get_tip()=="tip3");
  assert(list[2].get_model()=="model2");
  assert(list[2].get_an()==2022);
  assert(list[2].get_culoare()=="black");
  assert(list[2].get_pret()==3700);
};

void test_filter(){
  repository repo{"inputtest.txt"};
  services serv{repo};

  vector<device> list1 = serv.filterByModel("model3");
  assert(list1.size()==1);
  assert(list1[0].get_tip()=="tip5");


  const int an =2002;
  vector<device> list2 = serv.filterByAn(an);
  assert(list1.size()==1);
  assert(list1[0].get_tip()=="tip5");

}

void test_all(){
  test_read();
  test_filter();
}

// clang-format on
