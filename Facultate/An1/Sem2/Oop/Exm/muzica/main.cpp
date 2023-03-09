#include "gui.h"
#include "services.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  repository repo{"input.txt"};
  services serv{repo};
  gui ui{serv};
  ui.show();
  return app.exec();
}
