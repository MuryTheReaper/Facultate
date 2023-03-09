#include "gui.h"
#include <QPainter>
void gui::initGUI() {
  setLayout(mainLy);

  QWidget *widTable = (new QWidget);
  QVBoxLayout *tableLy = (new QVBoxLayout);

  widTable->setLayout(tableLy);
  tableLy->addWidget(table);

  QWidget *widTable2 = (new QWidget);
  QVBoxLayout *tableLy2 = (new QVBoxLayout);
  customTable->setModel(model);
  widTable2->setLayout(tableLy2);
  tableLy2->addWidget(customTable);

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

  mainLy->addWidget(widTable);
  mainLy->addWidget(widTable2);
  mainLy->addWidget(widModify);
  this->setMinimumHeight(400);
}

void gui::connect_signals() {

  QObject::connect(customTable, &QTableView::clicked, this, [&]() {
    int row = customTable->currentIndex().row();
    txtTitlu->setText(model->index(row, 1).data().toString());
  });

  QObject::connect(modifyButton, &QPushButton::clicked, this, &gui::modifyRank);
}

void gui::reloadList(const vector<melodie> &list) {
  this->table->clear();
  table->setColumnCount(4);
  table->setRowCount(int(list.size()));
  QStringList header = {"Id", "Titilu", "Artist", "Rank"};
  table->setHorizontalHeaderLabels(header);
  int row = 0;
  for (const auto &x : list) {
    QTableWidgetItem *itemId = (new QTableWidgetItem);
    QTableWidgetItem *itemTitlu = (new QTableWidgetItem);
    QTableWidgetItem *itemArtist = (new QTableWidgetItem);
    QTableWidgetItem *itemRank = (new QTableWidgetItem);

    itemId->setText(QString::fromStdString(std::to_string(x.getId())));
    itemTitlu->setText(QString::fromStdString(x.getTitlu()));
    itemArtist->setText(QString::fromStdString(x.getArtist()));
    itemRank->setText(QString::fromStdString(std::to_string(x.getRank())));

    this->table->setItem(row, 0, itemId);
    this->table->setItem(row, 1, itemTitlu);
    this->table->setItem(row, 2, itemArtist);
    this->table->setItem(row, 3, itemRank);
    row++;
  }

  model->setlist(serv.raportSameRank());
}

void gui::modifyRank() {
  try {
    int newRank = sliderRank->value();
    int row = customTable->currentIndex().row();
    int id = model->index(row, 0).data().toString().toInt();

    melodie x = serv.find(id, "", "", 0);
    serv.modify(x.getId(), x.getTitlu(), x.getArtist(), newRank);
    reloadList(serv.sortByRank());
  } catch (std::exception &ex) {
    QMessageBox::warning(this, "Warning", "Eroare");
  }
}

void gui::paintEvent(QPaintEvent *ev) {
  QPainter p{this};
  const int initialHeight = 10;
  const int maxrandom = 100;

  p.drawLine(10, this->height(), 10, 200);
  /*int h = initialHeight;
  for (int i = 0; i < contr.get_all().size(); i++) {
    p.drawLine(0, h, width(), h);
    h += (initialHeight + rand() % maxrandom);
    h = h % height();
  }*/
}
