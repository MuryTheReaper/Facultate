#include "gui.h"
#include <QMessageBox>
#include <QPainter>
#include <exception>

void gui::initGUI() {
  setLayout(mainLy);

  QWidget *widList = (new QWidget);
  QVBoxLayout *listLy = (new QVBoxLayout);

  widList->setLayout(listLy);
  listLy->addWidget(list);

  QWidget *widForm = (new QWidget);
  QFormLayout *formLy = (new QFormLayout);

  widForm->setLayout(formLy);
  formLy->addRow("Tip (Model): ", txtmodel);
  formLy->addRow("An: ", txtan);

  QWidget *widButtons = (new QWidget);
  QHBoxLayout *buttonsLy = (new QHBoxLayout);
  widButtons->setLayout(buttonsLy);
  buttonsLy->addWidget(btnFilterByModel);
  buttonsLy->addWidget(btnFilterByAn);
  buttonsLy->addWidget(reload);

  formLy->addRow(widButtons);

  mainLy->addWidget(widList);
  mainLy->addWidget(widForm);
}

void gui::connect_signals() {

  QObject::connect(btnFilterByModel, &QPushButton::clicked, this,
                   &gui::filterByModel);

  QObject::connect(btnFilterByAn, &QPushButton::clicked, this,
                   &gui::filterByAn);

  QObject::connect(list, &QListWidget::itemSelectionChanged, this, [&]() {
    auto selected = list->selectedItems();
    if (selected.isEmpty()) {
      txtmodel->setText("");
      txtan->setText("");
    } else {
      auto item = selected.at(0);
      string txt = item->data(Qt::UserRole).toString().toStdString();
      int space = int(txt.find("|"));
      string model;
      model.append(txt.begin(), txt.begin() + space);
      string pret;
      pret.append(txt.begin() + 1 + space, txt.end());

      txtmodel->setText(QString::fromStdString(model));
      txtan->setText(QString::fromStdString(pret));
    }
  });

  QObject::connect(reload, &QPushButton::clicked, this,
                   [&]() { reloadList(serv.get_all()); });
};

void gui::reloadList(const vector<device> &list) {
  this->list->clear();
  for (const auto &x : list) {
    QListWidgetItem *item = (new QListWidgetItem);
    string txt = x.get_model() + " (" + std::to_string(x.get_pret()) + ")";
    item->setText(QString::fromStdString(txt));
    this->list->addItem(item);

    item->setData(
        Qt::UserRole,
        QString::fromStdString(x.get_tip() + "|" + std::to_string(x.get_an())));

    const int minAn = 2019;
    if (x.get_an() > minAn) {
      if (x.get_culoare() == "green") {
        item->setData(Qt::BackgroundRole, QBrush{Qt::green, Qt::SolidPattern});
      } else if (x.get_culoare() == "red") {
        item->setData(Qt::BackgroundRole, QBrush{Qt::red, Qt::SolidPattern});
      } else if (x.get_culoare() == "blue") {
        item->setData(Qt::BackgroundRole, QBrush{Qt::blue, Qt::SolidPattern});
      } else if (x.get_culoare() == "black") {
        item->setData(Qt::BackgroundRole, QBrush{Qt::black, Qt::SolidPattern});
      } else if (x.get_culoare() == "yellow") {
        item->setData(Qt::BackgroundRole, QBrush{Qt::yellow, Qt::SolidPattern});
      }
    }
  }
}

void gui::filterByModel() {
  try {
    reloadList(serv.filterByModel(txtmodel->text().toStdString()));
  } catch (std::exception &ex) {
    QMessageBox::warning(this, "Warning", "Inavlid Model");
  }
}

void gui::filterByAn() {
  try {
    reloadList(serv.filterByAn(std::stoi(txtan->text().toStdString())));
  } catch (std::exception &ex) {
    QMessageBox::warning(this, "Warning", "Inavlid An");
  }
}
