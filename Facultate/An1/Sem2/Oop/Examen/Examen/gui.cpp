#include "gui.h"
#include <QPainter>
#include <iostream>
void gui::initGUI() {
  setLayout(mainLy);

  QWidget *widTable = (new QWidget);
  QVBoxLayout *tableLy = (new QVBoxLayout);
  customTable->setModel(model);
  widTable->setLayout(tableLy);
  tableLy->addWidget(customTable);
  const int spacing = 100;
  tableLy->addSpacing(spacing);

  QWidget *widModify = (new QWidget);
  QVBoxLayout *modifyLy = (new QVBoxLayout);
  const int maxi = 10;
  sliderRank->setTickInterval(1);
  sliderRank->setMinimum(0);
  sliderRank->setMaximum(maxi);

  widModify->setLayout(modifyLy);
  modifyLy->addWidget(txtTitlu);
  modifyLy->addWidget(sliderRank);
  modifyLy->addWidget(modifyButton);
  modifyLy->addWidget(deleteButton);

  mainLy->addWidget(widTable);
  mainLy->addWidget(widModify);

  const int minH = 600;
  this->setMinimumHeight(minH);
  this->setMinimumWidth(minH * 2);
}

void gui::connect_signals() {

  QObject::connect(customTable, &QTableView::clicked, this, [&]() {
    int row = customTable->currentIndex().row();
    txtTitlu->setText(model->index(row, 1).data().toString());
  });

  QObject::connect(modifyButton, &QPushButton::clicked, this, &gui::modifyRank);

  QObject::connect(deleteButton, &QPushButton::clicked, this,
                   &gui::deleteMelodie);
}

void gui::reloadList(const vector<std::pair<melodie, int>> &list) {

  model->setlist(list);
}

void gui::modifyRank() {
  try {
    int newRank = sliderRank->value();
    int row = customTable->currentIndex().row();
    int id = model->index(row, 0).data().toString().toInt();

    melodie x = serv.find(id, "", "", 0);
    serv.modify(x.getId(), txtTitlu->text().toStdString(), x.getArtist(),
                newRank);
    reloadList(serv.raportSameRank());
    this->repaint();
  } catch (std::exception &ex) {
    QMessageBox::warning(this, "Warning", "Eroare");
  }
}

void gui::deleteMelodie() {

  try {
    int row = customTable->currentIndex().row();
    int id = model->index(row, 0).data().toString().toInt();
    melodie x = serv.find(id, "", "", 0);
    serv.remove(x.getId(), x.getTitlu(), x.getArtist(), x.getRank());
    reloadList(serv.raportSameRank());
    this->repaint();
  } catch (std::exception &ex) {
    QMessageBox::warning(this, "Warning", "Ultima melodie");
  }
}

void gui::paintEvent(QPaintEvent *ev) {
  QPainter p{this};
  const int initial = 10;
  const int multi = 10;
  const int bare = 10;
  const int min = 20;
  int spatiu = initial;

  vector<int> ranks{serv.nrRank()};
  for (int i = 0; i <= bare; i++) {
    p.drawLine(spatiu, this->height(), spatiu,
               this->height() - ranks[i] * multi - min);
    spatiu += initial;
  }
  // p.drawLine(20, this->height(), 20, 5 * ranks[1]);
}
