#include "gui.h"
#include <QCloseEvent>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QMessageBox>
#include <QPainter>

void guiMain::initGUI() {
  setLayout(mainly);

  // formul din dreapta
  QGroupBox *widForm = (new QGroupBox);
  QFormLayout *formLayout = (new QFormLayout);
  widForm->setTitle("Discipline");
  widForm->setLayout(formLayout);

  QLabel *x = (new QLabel("Denumire:"));
  formLayout->addRow(x, txtDenumire);

  x = (new QLabel("Tip:"));
  formLayout->addRow(x, txtTip);

  x = (new QLabel("Profesor:"));
  formLayout->addRow(x, txtProfesor);

  x = (new QLabel("Ore:"));
  formLayout->addRow(x, txtOre);

  // butoane de sub form
  // butoane pt introducere txt
  QWidget *formbtn1 = (new QWidget);
  QWidget *formbtn2 = (new QWidget);
  QHBoxLayout *formbtnLayout1 = (new QHBoxLayout);
  QHBoxLayout *formbtnLayout2 = (new QHBoxLayout);

  formbtn1->setLayout(formbtnLayout1);

  formbtnLayout1->addWidget(btnAdd);
  formbtnLayout1->addWidget(btnModify);
  formbtnLayout1->addWidget(btnFind);

  formbtn2->setLayout(formbtnLayout2);

  formbtnLayout2->addWidget(btnRemove);
  formbtnLayout2->addWidget(btnUndo);

  formLayout->addRow(btnAddrandom, spinAddrandom);
  formLayout->addRow(formbtn1);
  formLayout->addRow(formbtn2);

  // butoane pentru filtrare
  QWidget *formbtnfilter = (new QWidget);
  QHBoxLayout *formbtnfilterLayout = (new QHBoxLayout);

  formbtnfilter->setLayout(formbtnfilterLayout);

  comboFilter->addItem("FilterByProf");
  comboFilter->addItem("FilterByOreUp");

  formbtnfilterLayout->addWidget(btnFilter);
  formbtnfilterLayout->addWidget(comboFilter);

  formLayout->addRow(formbtnfilter);

  // buton pentru contract
  //  QWidget *btncontract = (new QWidget);
  //  QHBoxLayout *btncontractLayout = (new QHBoxLayout);

  //  btncontract->setLayout(btncontractLayout);

  //  btncontractLayout->addWidget(btnOpenContract);

  //  formLayout->addRow(btncontract);
  // lista cu date
  QWidget *widList = (new QWidget);
  QVBoxLayout *ListLayout = (new QVBoxLayout);
  widList->setLayout(ListLayout);
  ListLayout->addWidget(list);

  // butoane de sub lista
  QWidget *listbtn = (new QWidget);
  QHBoxLayout *listbtnLayout = (new QHBoxLayout);

  listbtn->setLayout(listbtnLayout);

  // listbtnLayout->addWidget(btnSortByDenumire);
  // listbtnLayout->addWidget(btnSortByOre);

  comboSort->addItem("SortByDenumire");
  comboSort->addItem("SortByOre");
  comboSort->addItem("SortByMixt");

  listbtnLayout->addWidget(btnSort);
  listbtnLayout->addWidget(comboSort);
  listbtnLayout->addWidget(btnReload);

  ListLayout->addWidget(listbtn);

  // contract
  QGroupBox *widContract = (new QGroupBox);
  QFormLayout *contractLayout = (new QFormLayout);
  widContract->setLayout(contractLayout);
  widContract->setTitle("Contract");

  contractLayout->addRow(btnAddContract);
  contractLayout->addRow(btnGenerateContract, spinGenerate);
  contractLayout->addRow(btnDeleteContract);
  contractLayout->addRow(btnExportContract, txtExport);
  contractLayout->addRow(btnOpenContract);
  contractLayout->addRow(btnOpenContractROnly);

  // construire fereastra
  mainly->addWidget(widList);
  mainly->addWidget(widForm);
  mainly->addWidget(widContract);
}

void guiMain::connect_signals() {

  QObject::connect(btnAddContract, &QPushButton::clicked, this,
                   &guiMain::addContract);

  QObject::connect(btnGenerateContract, &QPushButton::clicked, this,
                   &guiMain::generateContract);

  QObject::connect(btnDeleteContract, &QPushButton::clicked, this,
                   &guiMain::deleteContract);

  QObject::connect(btnExportContract, &QPushButton::clicked, this,
                   &guiMain::exportContract);

  QObject::connect(btnAdd, &QPushButton::clicked, this,
                   &guiMain::addDisciplina);

  QObject::connect(btnModify, &QPushButton::clicked, this,
                   &guiMain::modifyDisciplina);

  QObject::connect(btnRemove, &QPushButton::clicked, this,
                   &guiMain::removeDisciplina);

  QObject::connect(btnFind, &QPushButton::clicked, this,
                   &guiMain::findDisciplina);

  QObject::connect(btnUndo, &QPushButton::clicked, this,
                   &guiMain::undoDisciplina);

  //  QObject::connect(btnFilter, &QPushButton::clicked, this,
  //                   &guiMain::filterDisciplina);

  //  QObject::connect(btnFilterByProf, &QPushButton::clicked, this,
  //                   &guiMain::filterByProfDisciplina);

  //  QObject::connect(btnSortByDenumire, &QPushButton::clicked, this,
  //                   &guiMain::sortByDenumireDisciplina);

  //  QObject::connect(btnSortByOre, &QPushButton::clicked, this,
  //                   &guiMain::sortByOreDisciplina);

  //  QObject::connect(btnSortByMixt, &QPushButton::clicked, this,
  //                   &guiMain::sortByMixtDisciplina);

  QObject::connect(btnFilter, &QPushButton::clicked, this,
                   &guiMain::filterDisciplina);

  QObject::connect(btnSort, &QPushButton::clicked, this,
                   &guiMain::sortDisciplina);

  QObject::connect(btnAddrandom, &QPushButton::clicked, this,
                   &guiMain::addRandom);

  QObject::connect(list, &QListWidget::itemSelectionChanged, this, [&]() {
    auto selected = list->selectedItems();
    if (selected.isEmpty()) {
      txtDenumire->setText("");
      txtTip->setText("");
      txtProfesor->setText("");
      txtOre->setText("");
    } else {
      auto item = selected.at(0);
      auto denumire = item->data(Qt::UserRole).toString().toStdString();
      disciplina x = serv.find(denumire, "1", ".", ".");
      txtDenumire->setText(QString::fromStdString(x.get_denumire()));
      txtTip->setText(QString::fromStdString(x.get_tip()));
      txtProfesor->setText(QString::fromStdString(x.get_profesor()));
      txtOre->setText(QString::fromStdString(std::to_string(x.get_ore())));
    }
  });

  QObject::connect(btnOpenContract, &QPushButton::clicked, this, [&]() {
    guiContract *x = (new guiContract{serv.getContract()});
    x->show();
  });

  QObject::connect(btnOpenContractROnly, &QPushButton::clicked, this, [&]() {
    guiContractDraw *x = (new guiContractDraw{serv.getContract()});
    x->show();
  });

  QObject::connect(btnReload, &QPushButton::clicked, this,
                   [&]() { reloadList(serv.get_all()); });
}

void guiMain::addDisciplina() {
  try {
    serv.add(txtDenumire->text().toStdString(), txtOre->text().toStdString(),
             txtTip->text().toStdString(), txtProfesor->text().toStdString());
    reloadList(serv.get_all());
  } catch (repoException &ex) {
    QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
  } catch (validateException &ex) {
    QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
  }
}

void guiMain::modifyDisciplina() {
  try {
    serv.modify(txtDenumire->text().toStdString(), txtOre->text().toStdString(),
                txtTip->text().toStdString(),
                txtProfesor->text().toStdString());
    reloadList(serv.get_all());
  } catch (repoException &ex) {
    QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
  } catch (validateException &ex) {
    QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
  }
}

void guiMain::removeDisciplina() {
  try {
    serv.remove(txtDenumire->text().toStdString(), txtOre->text().toStdString(),
                txtTip->text().toStdString(),
                txtProfesor->text().toStdString());
    reloadList(serv.get_all());
  } catch (repoException &ex) {
    QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
  } catch (validateException &ex) {
    QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
  }
}

void guiMain::findDisciplina() {
  try {
    disciplina const &x =
        serv.find(txtDenumire->text().toStdString(), "1", ".", ".");

    reloadList(serv.get_all());
    auto items = list->findItems(QString::fromStdString(x.get_denumire()),
                                 Qt::MatchStartsWith);
    items[0]->setData(Qt::BackgroundRole, QBrush{Qt::green, Qt::SolidPattern});
  } catch (repoException &ex) {
    QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
  } catch (validateException &ex) {
    QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
  }
}

void guiMain::undoDisciplina() {
  try {
    serv.undo();
    reloadList(serv.get_all());
  } catch (repoException &ex) {
    QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
  } catch (validateException &ex) {
    QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
  } catch (servException &ex) {
    QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
  }
}

// void guiMain::filterByProfDisciplina() {
//   try {
//     reloadList(serv.filter_profesor(txtProfesor->text().toStdString()));
//   } catch (repoException &ex) {
//     QMessageBox::warning(this, "Warning",
//     QString::fromStdString(ex.getMsg()));
//   } catch (validateException &ex) {
//     QMessageBox::warning(this, "Warning",
//     QString::fromStdString(ex.getMsg()));
//   }
// }

// void guiMain::filterByOreDisciplina() {
//   try {
//     reloadList(serv.filter_ore_up(txtOre->text().toStdString()));
//   } catch (repoException &ex) {
//     QMessageBox::warning(this, "Warning",
//     QString::fromStdString(ex.getMsg()));
//   } catch (validateException &ex) {
//     QMessageBox::warning(this, "Warning",
//     QString::fromStdString(ex.getMsg()));
//   }
// }

void guiMain::filterDisciplina() {
  try {
    if (comboFilter->currentIndex() == 0) {
      reloadList(serv.filter_profesor(txtProfesor->text().toStdString()));
    } else if (comboFilter->currentIndex() == 1) {
      reloadList(serv.filter_ore_up(txtOre->text().toStdString()));
    }
  } catch (repoException &ex) {
    QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
  } catch (validateException &ex) {
    QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
  }
}
// void guiMain::sortByDenumireDisciplina() {
//   try {
//     reloadList(serv.sort_denumire());
//   } catch (repoException &ex) {
//     QMessageBox::warning(this, "Warning",
//     QString::fromStdString(ex.getMsg()));
//   } catch (validateException &ex) {
//     QMessageBox::warning(this, "Warning",
//     QString::fromStdString(ex.getMsg()));
//   }
// }

// void guiMain::sortByOreDisciplina() {
//   try {
//     reloadList(serv.sort_ore());
//   } catch (repoException &ex) {
//     QMessageBox::warning(this, "Warning",
//     QString::fromStdString(ex.getMsg()));
//   } catch (validateException &ex) {
//     QMessageBox::warning(this, "Warning",
//     QString::fromStdString(ex.getMsg()));
//   }
// }

// void guiMain::sortByMixtDisciplina() {
//   try {
//     reloadList(serv.sort_mix());
//   } catch (repoException &ex) {
//     QMessageBox::warning(this, "Warning",
//     QString::fromStdString(ex.getMsg()));
//   } catch (validateException &ex) {
//     QMessageBox::warning(this, "Warning",
//     QString::fromStdString(ex.getMsg()));
//   }
// }

void guiMain::sortDisciplina() {

  try {
    if (comboSort->currentIndex() == 0) {
      reloadList(serv.sort_denumire());
    } else if (comboSort->currentIndex() == 1) {
      reloadList(serv.sort_ore());
    } else if (comboSort->currentIndex() == 2) {
      reloadList(serv.sort_mix());
    }
  } catch (repoException &ex) {
    QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
  } catch (validateException &ex) {
    QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
  }
}

void guiMain::addContract() {
  try {
    auto selected = list->selectedItems();
    if (selected.isEmpty()) {
      QMessageBox::warning(this, "Warning", "Nu este nimic selectat");
      return;
    }
    auto item = selected.at(0);

    std::string denumire = item->data(Qt::UserRole).toString().toStdString();

    serv.add_to_contract(denumire, "1", ".", ".");

  } catch (contractException &ex) {
    QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
  } catch (validateException &ex) {
    QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
  }
}

void guiMain::generateContract() {
  serv.addrandom_to_contract(spinGenerate->value());
}

void guiMain::deleteContract() { serv.delete_all_contract(); }

void guiMain::exportContract() {
  if (txtExport->text() == "") {
    QMessageBox::warning(this, "Warning", "Introdu numele fisierului");
  } else
    serv.export_contract(txtExport->text().toStdString());
}

void guiMain::reloadList(const std::vector<disciplina> &list) {
  this->list->clear();
  for (const auto &x : list) {
    QListWidgetItem *item = (new QListWidgetItem);

    std::string txt =
        x.get_denumire() + " | " + x.get_tip() + " | " + x.get_profesor();
    txt.append(" | ");
    txt.append(std::to_string(x.get_ore()));

    item->setText(QString::fromStdString(txt));
    item->setData(Qt::UserRole, QString::fromStdString(x.get_denumire()));
    this->list->addItem(item);
  }
}

void guiMain::addRandom() {
  try {
    serv.addrandom(std::to_string(spinAddrandom->value()));
    reloadList(serv.get_all());
  } catch (repoException &ex) {
    QMessageBox::warning(this, "Warning", "Nu s-au introdus toate elementele");
    reloadList(serv.get_all());
  } catch (validateException &ex) {
    QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
  }
}

void guiContract::initGUI() {

  setLayout(mainly);
  table->setModel(model);

  // lista cu date
  QWidget *widList = (new QWidget);
  QVBoxLayout *ListLayout = (new QVBoxLayout);
  widList->setLayout(ListLayout);
  ListLayout->addWidget(table);

  // butoane din dreapta
  QWidget *widBtn = (new QWidget);
  QFormLayout *btnLayout = (new QFormLayout);

  widBtn->setLayout(btnLayout);

  btnLayout->addRow(btnAdd, txtAdd);
  btnLayout->addRow(btnGenerate, spinGenerate);
  btnLayout->addRow(btnDelete);
  // btnLayout->addRow(btnExport, txtExport);

  // construiere fereastra
  mainly->addWidget(widList);
  mainly->addWidget(widBtn);
}

void guiContract::connect_signals() {

  contr.addObserver(this);

  QObject::connect(btnAdd, &QPushButton::clicked, this,
                   &guiContract::addContract);

  QObject::connect(btnGenerate, &QPushButton::clicked, this,
                   &guiContract::generateContract);

  QObject::connect(btnDelete, &QPushButton::clicked, this,
                   &guiContract::deleteContract);

  //  QObject::connect(btnExport, &QPushButton::clicked, this,
  //                   &guiContract::exportContract);
}

void guiContract::addContract() {

  try {
    std::string denumire = txtAdd->text().toStdString();
    disciplina x{denumire, 1, ".", "."};
    x = contr.get_repo().find(x);
    contr.add_to_contract(x);
  } catch (repoException &ex) {
    QMessageBox::warning(this, "Warning", "Nu exsita disciplina");
  } catch (validateException &ex) {
    QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
  } catch (contractException &ex) {
    QMessageBox::warning(this, "Warning", "Exsita disciplina deja in contract");
  }

  /*try {
    auto selected = mainui.list->selectedItems();
    if (selected.isEmpty()) {
      QMessageBox::warning(this, "Warning", "Nu este nimic selectat");
      return;
    }
    auto item = selected.at(0);

    std::string denumire =
  item->data(Qt::UserRole).toString().toStdString();

    mainui.serv.add_to_contract(denumire, "1", ".", ".");
    reloadList(mainui.serv.get_all_contract());

  } catch (contractException &ex) {
    QMessageBox::warning(this, "Warning",
  QString::fromStdString(ex.getMsg())); } catch (validateException &ex) {
    QMessageBox::warning(this, "Warning",
  QString::fromStdString(ex.getMsg()));
  }*/
}

void guiContract::generateContract() {

  contr.addrandom_to_contract(spinGenerate->value());
  reloadList(contr.get_all());
}

void guiContract::deleteContract() {

  contr.delete_all();
  reloadList(contr.get_all());
}

// void guiContract::exportContract() {

//  //  if (txtExport->text() == "") {
//  //    QMessageBox::warning(this, "Warning", "Introdu numele
//  fisierului");
//  //  } else
//  //    mainui.serv.export_contract(txtExport->text().toStdString());
//}

void guiContract::reloadList(const std::vector<disciplina> &list) {
  /*this->table->clear();
  table->setColumnCount(4);
  table->setRowCount(int(list.size()));
  QStringList header = {"Denumire", "Tip", "Profesor", "Ore"};
  table->setHorizontalHeaderLabels(header);
  int row = 0;
  for (const auto &x : list) {
    QTableWidgetItem *itemDenumire = (new QTableWidgetItem);
    QTableWidgetItem *itemTip = (new QTableWidgetItem);
    QTableWidgetItem *itemProfesor = (new QTableWidgetItem);
    QTableWidgetItem *itemOre = (new QTableWidgetItem);

    itemDenumire->setText(QString::fromStdString(x.get_denumire()));
    itemTip->setText(QString::fromStdString(x.get_tip()));
    itemProfesor->setText(QString::fromStdString(x.get_profesor()));
    itemOre->setText(QString::fromStdString(std::to_string(x.get_ore())));

    this->table->setItem(row, 0, itemDenumire);
    this->table->setItem(row, 1, itemTip);
    this->table->setItem(row, 2, itemProfesor);
    this->table->setItem(row, 3, itemOre);
    row++;
  }*/
  model->setlist(list);
}

void guiContractDraw::paintEvent(QPaintEvent *ev) {
  QPainter p{this};
  const int initialHeight = 10;
  const int maxrandom = 100;
  int h = initialHeight;
  for (int i = 0; i < contr.get_all().size(); i++) {
    p.drawLine(0, h, width(), h);
    h += (initialHeight + rand() % maxrandom);
    h = h % height();
  }
}
