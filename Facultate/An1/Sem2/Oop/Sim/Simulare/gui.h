#ifndef GUI_H
#define GUI_H
#include "services.h"
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class gui : public QWidget {
private:
  // adresa catre serv
  services &serv;
  // layout-ul ferestrei
  QHBoxLayout *mainLy = (new QHBoxLayout);
  // Lista cu date
  QListWidget *list = (new QListWidget);
  // LineEdit pt detalii
  QLineEdit *txtmodel = (new QLineEdit);
  QLineEdit *txtan = (new QLineEdit);
  // butoane pt filtrare
  QPushButton *btnFilterByModel = (new QPushButton("Filtrare Model"));
  QPushButton *btnFilterByAn = (new QPushButton("Filtrare An"));
  QPushButton *reload = (new QPushButton("Reincarcare"));
  void initGUI();
  void connect_signals();
  void reloadList(const vector<device> &list);

  void filterByModel();
  void filterByAn();

public:
  gui(services &serv) : serv{serv} {
    initGUI();
    connect_signals();
    reloadList(serv.get_all());
  };
};
#endif // GUI_H
