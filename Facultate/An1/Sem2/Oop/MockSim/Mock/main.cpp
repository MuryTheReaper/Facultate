#include "services.h"
#include "tests.h"
#include "ui.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  repository repo{"input.txt"};
  services serv{repo};
  ui gui{serv};
  gui.show();
  return app.exec();
  // run_tests();
}
