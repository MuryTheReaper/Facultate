#ifndef GUI_H
#define GUI_H

#include "QHBoxLayout"
#include "myTableModel.h"
#include "services.h"
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>
#include <QTableWidget>
#include <QWidget>

class gui : public QWidget {
private:
  services &serv;
  QHBoxLayout *mainLy = (new QHBoxLayout);

  QTableWidget *table = (new QTableWidget);
  CustomTableModel *model = (new CustomTableModel{serv.raportSameRank()});
  QTableView *customTable = (new QTableView);

  QLineEdit *txtTitlu = (new QLineEdit);
  QSlider *sliderRank = (new QSlider{Qt::Horizontal});
  QPushButton *modifyButton = (new QPushButton("Modify"));

  void initGUI();
  void connect_signals();
  void reloadList(const vector<melodie> &list);
  void paintEvent(QPaintEvent *ev) override;
  void modifyRank();

public:
  gui(services &serv) : serv{serv} {
    initGUI();
    connect_signals();
    reloadList(serv.sortByRank());
  };
};

#endif // GUI_H
