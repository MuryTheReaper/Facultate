#include "gui.h"
#include "ui.h"
#include "validator.h"
#include <QtWidgets/QApplication>

void runGUI(int argc, char **argv) {
  QApplication app(argc, argv);
  repository repo;
  validator val;
  services serv{repo, val};
  guiMain ui{serv};
  ui.show();
  app.exec();
}

int main(int argc, char **argv) {

  runGUI(argc, argv);

  // std::cout << "END\n";
  return 0;
}
