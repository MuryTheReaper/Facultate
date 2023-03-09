#include "ui.h"
#include <QFormLayout>
void ui::initGUI() {
  setLayout(mainly);
  QWidget *widList = (new QWidget);
  QVBoxLayout *listLay = (new QVBoxLayout);
  widList->setLayout(listLay);
  listLay->addWidget(list);

  QWidget *widForm = (new QWidget);
  QFormLayout *formLy = (new QFormLayout);
  widForm->setLayout(formLy);
  txtmodel->setReadOnly(true);
  txtpret->setReadOnly(true);
  formLy->addRow("Model: ", txtmodel);
  formLy->addRow("Pret: ", txtpret);

  mainly->addWidget(widList);
  mainly->addWidget(widForm);
}

void ui::connect_signals() {

  QObject::connect(list, &QListWidget::itemSelectionChanged, this, [&]() {
    auto selected = list->selectedItems();
    if (selected.isEmpty()) {
      txtmodel->setText("");
      txtpret->setText("");
    } else {
      auto item = selected.at(0);
      string txt = item->data(Qt::UserRole).toString().toStdString();
      int space = int(txt.find("|"));
      string model;
      model.append(txt.begin(), txt.begin() + space);
      string pret;
      pret.append(txt.begin() + 1 + space, txt.end());

      txtmodel->setText(QString::fromStdString(model));
      txtpret->setText(QString::fromStdString(pret));
    }
  });
};

void ui::reloadList(const vector<device> &list) {
  this->list->clear();
  for (const auto &x : list) {
    QListWidgetItem *item = (new QListWidgetItem);

    std::string txt = x.get_tip() + " | " + x.get_model();
    txt.append(" | ");
    txt.append(std::to_string(x.get_an()));
    txt.append(" | ");
    txt.append(x.get_culoare());
    txt.append(" | ");
    txt.append(std::to_string(x.get_pret()));

    item->setText(QString::fromStdString(txt));
    item->setData(Qt::UserRole,
                  QString::fromStdString(x.get_model() + "|" +
                                         std::to_string(x.get_pret())));
    if (x.get_culoare() == "green") {
      item->setData(Qt::BackgroundRole, QBrush{Qt::green, Qt::SolidPattern});
    } else if (x.get_culoare() == "red") {
      item->setData(Qt::BackgroundRole, QBrush{Qt::red, Qt::SolidPattern});
    } else if (x.get_culoare() == "blue") {
      item->setData(Qt::BackgroundRole, QBrush{Qt::blue, Qt::SolidPattern});
    } else if (x.get_culoare() == "black") {
      item->setData(Qt::BackgroundRole, QBrush{Qt::black, Qt::SolidPattern});
    }
    this->list->addItem(item);
  }
};
