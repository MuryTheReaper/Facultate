#include "ui.h"
#include <algorithm>
#include <chrono>
#include <random>
#include <string>

void ui::print(const std::vector<disciplina> x) {

  std::cout << "DISCIPLINE: \n\n";
  for (const auto &d : x) {
    std::cout << d.get_denumire() << " " << d.get_tip() << " "
              << d.get_profesor() << " " << d.get_ore() << "\n";
  }
  std::cout << "_____________\n";
}

void ui::add_ui() {

  std::string d, t, p, o;

  std::cout << "Denumire: ";
  std::cin >> d;

  std::cout << "Tip: ";
  std::cin >> t;

  std::cout << "Profesor: ";
  std::cin >> p;

  std::cout << "Ore: ";
  std::cin >> o;

  serv.add(d, o, t, p);

  std::cout << "Adaugat cu succes\n";
}

void ui::add_random_ui() {

  std::string nr;
  std::cout << "Numar de discipline: \n";
  std::cin >> nr;
  try {
    int n = std::stoi(nr);
    while (n) {
      std::mt19937 mt{std::random_device{}()};
      const int size = 1000;
      std::uniform_int_distribution<> dist(0, size - 1);
      std::string o =
          std::to_string(dist(mt)); // numar aleator intre [0,size-1]

      const int size_l = 10;
      auto randchar = []() -> char {
        const std::string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                    "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (charset.size() - 1);
        return charset[rand() % max_index];
      };
      std::uniform_int_distribution<> dist_l(1, size_l - 1);
      const int length = dist_l(mt);
      std::string d(length, 0);
      std::string t(length, 0);
      std::string p(length, 0);

      std::generate_n(d.begin(), length, randchar);
      std::generate_n(t.begin(), length, randchar);
      std::generate_n(p.begin(), length, randchar);

      serv.add(d, o, t, p);
      n--;
    }
    std::cout << "Adaugat cu succes\n";

  } catch (const std::invalid_argument &e) {
    std::cout << "Numar invalid\n";
  }
}

void ui::remove_ui() {

  std::string d, t, p, o;

  std::cout << "Denumire: ";
  std::cin >> d;

  t = ".";
  p = ".";
  o = "1";
  serv.remove(d, o, t, p);

  std::cout << "Sters cu succes\n";
}

void ui::find_ui() {

  std::string d, t, p, o;

  std::cout << "Denumire: ";
  std::cin >> d;

  t = ".";
  p = ".";
  o = "1";
  disciplina x = serv.find(d, o, t, p);

  std::cout << x.get_denumire() << " " << x.get_tip() << " " << x.get_profesor()
            << " " << x.get_ore() << "\n";
}

void ui::modify_ui() {

  std::string d, t, p, o;

  std::cout << "Denumire disciplinei de modificat: ";
  std::cin >> d;

  std::cout << "Noul Tip: ";
  std::cin >> t;

  std::cout << "Noul Profesor: ";
  std::cin >> p;

  std::cout << "Noul numer de Ore: ";
  std::cin >> o;

  serv.modify(d, o, t, p);

  std::cout << "Modificat cu succes\n";
}

void ui::filter_ui() {

  std::string x, f;

  std::cout << "Filtrare dupa ore sau profesor(1/2): ";
  std::cin >> x;

  if (x == "1") {

    std::cout << "Mai mare decat: ";
    std::cin >> f;

    print(serv.filter_ore_up(f));
  } else if (x == "2") {
    std::cout << "Profesor: ";
    std::cin >> f;

    print(serv.filter_profesor(f));
  } else {
    std::cout << "Comanda invalida\n";
  }
}

void ui::sort_ui() {

  std::string x, f;

  std::cout << "Sortare dupa denumire, ore sau profesor+tip(1/2/3): ";
  std::cin >> x;

  if (x == "1") {
    print(serv.sort_denumire());
  } else if (x == "2") {
    print(serv.sort_ore());
  } else if (x == "3") {
    print(serv.sort_mix());
  } else {
    std::cout << "Comanda invalida\n";
  }
}

void ui::print_raport_prof_frec(
    const std::unordered_map<std::string, profesor_frecventa> &x) {

  std::cout << "RAPORT PROFESOR FRECVENTA\n";
  for (const auto &p : x) {
    std::cout << p.first << " -> " << p.second.get_frecventa() << "\n";
  }
  std::cout << "_____________\n";
}

void ui::raport_ui() {

  std::string x;

  std::cout << "Raport profesor frecventa(1)\n";
  std::cin >> x;

  if (x == "1") {
    print_raport_prof_frec(serv.raport_profesor_frecventa());
  } else {
    std::cout << "Comanda invalida\n";
  }
}

void ui::undo_ui() {

  serv.undo();
  std::cout << "Undo efectuat cu succes\n";
}

void ui::add_contract_ui() {

  std::string d, t, p, o;

  std::cout << "Denumire: ";
  std::cin >> d;

  t = ".";
  p = ".";
  o = "1";

  serv.add_to_contract(d, o, t, p);

  std::cout << "Adaugat cu succes\n";
  std::cout << "Dimensiunea contractului este: "
            << serv.get_all_contract().size() << "\n";
}

void ui::generate_contract_ui() {

  std::string n;

  std::cout << "Numar de discipline: ";
  std::cin >> n;

  try {
    long unsigned int nr = std::stoi(n);
    serv.addrandom_to_contract(nr);

    std::cout << "Adaugat cu succes\n";
    std::cout << "Dimensiunea contractului este: "
              << serv.get_all_contract().size() << "\n";

  } catch (const std::invalid_argument &e) {
    std::cout << "Numar invalid\n";
  }
}
void ui::delete_contract_ui() {
  serv.delete_all_contract();
  std::cout << "Sters cu succes\n";
}
void ui::export_contract_ui() {
  std::string file;

  std::cout << "File name: ";
  std::cin >> file;

  serv.export_contract(file);
  std::cout << "Exportat cu succes\n";
}
void ui::contract_ui() {

  while (true) {

    std::cout << "\nMENIU CONTRACT:\n";
    std::cout << "print\nadd\ngenerate\ndelete\nexport\nexit\nCOMANDA: ";

    std::string cmd;
    std::cin >> cmd;

    try {
      if (cmd == "print") {
        print(serv.get_all_contract());
      } else if (cmd == "add") {
        add_contract_ui();
      } else if (cmd == "generate") {
        generate_contract_ui();
      } else if (cmd == "delete") {
        delete_contract_ui();
      } else if (cmd == "export") {
        export_contract_ui();
      } else if (cmd == "exit") {
        return;
      } else {
        std::cout << "Comanda invalida\n";
      }
    } catch (const repoException &ex) {
      std::cout << ex << "\n";
    } catch (const validateException &ex) {
      std::cout << ex << "\n";
    }
  }
}

void ui::run() {

  while (true) {

    std::cout << "\nMENIU: \n";
    std::cout << "contract\nprint\nadd\nadd_random\nremove\nmodify\nfind\n"
                 "filter\nsort\nraport\nexit\nundo\nCOMANDA: ";

    std::string cmd;
    std::cin >> cmd;

    try {
      if (cmd == "print") {
        print(serv.get_all());
      } else if (cmd == "contract") {
        contract_ui();
      } else if (cmd == "add") {
        add_ui();
      } else if (cmd == "add_random") {
        add_random_ui();
      } else if (cmd == "remove") {
        remove_ui();
      } else if (cmd == "modify") {
        modify_ui();
      } else if (cmd == "find") {
        find_ui();
      } else if (cmd == "filter") {
        filter_ui();
      } else if (cmd == "sort") {
        sort_ui();
      } else if (cmd == "raport") {
        raport_ui();
      } else if (cmd == "undo") {
        undo_ui();
      } else if (cmd == "exit") {
        return;
      } else {
        std::cout << "Comanda invalida\n";
      }
    } catch (const repoException &ex) {
      std::cout << ex << "\n";
    } catch (const validateException &ex) {
      std::cout << ex << "\n";
    } catch (const servException &ex) {
      std::cout << ex << "\n";
    }
  }
}