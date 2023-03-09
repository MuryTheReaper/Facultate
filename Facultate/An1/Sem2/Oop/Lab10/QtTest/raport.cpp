#include "raport.h"
#include "disciplina.h"
#include <algorithm>
#include <functional>
#include <vector>

void raport::make_raport_prof_frec(const std::vector<disciplina> &list) {

  rap_prof_frec.clear();
  for (auto const &x : list) {
    profesor_frecventa e;
    e.set_profesor(x.get_profesor());
    e.set_frecventa(1);
    bool ok = rap_prof_frec.insert({x.get_profesor(), e}).second;
    if (!ok) {
      rap_prof_frec.at(x.get_profesor()).change_frecventa(1);
    }
  }
}
