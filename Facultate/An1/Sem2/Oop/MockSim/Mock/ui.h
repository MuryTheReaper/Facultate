#ifndef UI_H
#define UI_H
#include "services.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QVBoxLayout>
#include <QWidget>

class ui : public QWidget {
private:
  services &serv;
  QHBoxLayout *mainly = (new QHBoxLayout);
  QListWidget *list = (new QListWidget);
  QLineEdit *txtmodel = (new QLineEdit("Model"));
  QLineEdit *txtpret = (new QLineEdit("Pret"));
  void initGUI();
  void connect_signals();
  void reloadList(const vector<device> &list);

public:
  ui(services &serv) : serv{serv} {
    initGUI();
    connect_signals();
    reloadList(serv.get_all());
  };
};
#endif // UI_H
