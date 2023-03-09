#ifndef GUI_H
#define GUI_H

#include "QHBoxLayout"
#include "mytablemodel.h"
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

  CustomTableModel *model = (new CustomTableModel{serv.raportSameRank()});
  QTableView *customTable = (new QTableView);

  QLineEdit *txtTitlu = (new QLineEdit);
  QSlider *sliderRank = (new QSlider{Qt::Horizontal});
  QPushButton *modifyButton = (new QPushButton("Modify"));

  QPushButton *deleteButton = (new QPushButton("Delete"));

  void initGUI();
  void connect_signals();
  void reloadList(const vector<std::pair<melodie, int>> &list);
  void paintEvent(QPaintEvent *ev) override;
  void modifyRank();
  void deleteMelodie();

public:
  gui(services &serv) : serv{serv} {
    initGUI();
    connect_signals();
    reloadList(serv.raportSameRank());
  };
};

class guiDraw : public QWidget {
private:
  services &serv;
  void paintEvent(QPaintEvent *ev) override;

public:
  guiDraw(services &serv) : serv{serv} {};
};

#endif // GUI_H
