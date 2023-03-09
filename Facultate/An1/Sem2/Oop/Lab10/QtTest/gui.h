#ifndef GUI_H
#define GUI_H

#include "disciplina.h"
#include "myTableModel.h"
#include "services.h"
#include <QCloseEvent>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QSpinBox>
#include <QTableWidget>
#include <QWidget>

class guiMain : public QWidget {

private:
  services &serv;
  QHBoxLayout *mainly;
  QLineEdit *txtDenumire;
  QLineEdit *txtTip;
  QLineEdit *txtProfesor;
  QLineEdit *txtOre;
  QListWidget *list = (new QListWidget);
  QPushButton *btnAdd = (new QPushButton("Add"));
  QPushButton *btnModify = (new QPushButton("Modify"));
  QPushButton *btnFind = (new QPushButton("Find"));
  QPushButton *btnRemove = (new QPushButton("Remove"));
  QPushButton *btnUndo = (new QPushButton("Undo"));
  QPushButton *btnAddrandom = (new QPushButton("Random"));
  // contract
  QPushButton *btnAddContract = (new QPushButton("Add"));
  QPushButton *btnGenerateContract = (new QPushButton("Generate"));
  QPushButton *btnDeleteContract = (new QPushButton("Delete"));
  QPushButton *btnExportContract = (new QPushButton("Export"));
  QSpinBox *spinGenerate = (new QSpinBox);
  QLineEdit *txtExport = (new QLineEdit);
  QPushButton *btnOpenContract = (new QPushButton("ContractCRUD"));
  QPushButton *btnOpenContractROnly = (new QPushButton("ContractRead"));
  //
  QSpinBox *spinAddrandom = (new QSpinBox);
  //  QPushButton *btnFilterByProf = (new QPushButton("FilterByProfesor"));
  //  QPushButton *btnFilterByOre = (new QPushButton("FilterByOreUp"));
  QComboBox *comboFilter = (new QComboBox);
  QPushButton *btnFilter = (new QPushButton("Filter"));
  QComboBox *comboSort = (new QComboBox);
  QPushButton *btnSort = (new QPushButton("Sort"));
  QPushButton *btnReload = (new QPushButton("Reload"));
  //  QPushButton *btnSortByDenumire = (new QPushButton("SortByDenumire"));
  //  QPushButton *btnSortByOre = (new QPushButton("SortByOre"));
  //  QPushButton *btnSortByMixt = (new QPushButton("SortByMixt"));

  void initGUI();
  void connect_signals();
  void reloadList(const std::vector<disciplina> &list);

  void addDisciplina();
  void modifyDisciplina();
  void removeDisciplina();
  void findDisciplina();
  void undoDisciplina();
  //  void filterByProfDisciplina();
  //  void filterByOreDisciplina();
  void filterDisciplina();
  //  void sortByDenumireDisciplina();
  //  void sortByOreDisciplina();
  //  void sortByMixtDisciplina();
  void sortDisciplina();
  void addRandom();

  void addContract();
  void generateContract();
  void deleteContract();
  void exportContract();

public:
  guiMain(services &serv)
      : serv{serv}, mainly{new QHBoxLayout}, txtDenumire{new QLineEdit},
        txtTip{new QLineEdit}, txtProfesor{new QLineEdit}, txtOre{
                                                               new QLineEdit} {
    initGUI();
    connect_signals();
    reloadList(serv.get_all());
  }
};

class guiContract : public QWidget, public observer {
private:
  // guiMain &mainui;
  contract &contr;
  QHBoxLayout *mainly = (new QHBoxLayout);
  // QTableWidget *table = (new QTableWidget);
  QTableView *table = (new QTableView);
  CustomTableModel *model = (new CustomTableModel{contr.get_all()});
  QPushButton *btnAdd = (new QPushButton("Add"));
  QPushButton *btnGenerate = (new QPushButton("Generate"));
  QSpinBox *spinGenerate = (new QSpinBox);
  QPushButton *btnDelete = (new QPushButton("Delete"));
  // QPushButton *btnExport = (new QPushButton("Export"));
  QLineEdit *txtAdd = (new QLineEdit);

  void initGUI();
  void connect_signals();
  void reloadList(const std::vector<disciplina> &list);

  void addContract();
  void generateContract();
  void deleteContract();
  // void exportContract();

public:
  guiContract(contract &contr) : contr{contr} {
    initGUI();
    connect_signals();
    reloadList(contr.get_all());
  }

  void update() override { reloadList(contr.get_all()); }

  ~guiContract() override { contr.removeObserver(this); }

  guiContract(const guiContract &x) = delete;

  guiContract &operator=(const guiContract &) = delete;

  guiContract(guiContract &&) = delete;

  guiContract &operator=(guiContract &&) = delete;
};

class guiContractDraw : public QWidget, public observer {
private:
  contract &contr;

  void paintEvent(QPaintEvent *ev) override;

public:
  guiContractDraw(contract &contr) : contr{contr} { contr.addObserver(this); }

  void update() override { this->repaint(); }

  ~guiContractDraw() override { contr.removeObserver(this); }

  guiContractDraw(const guiContractDraw &x) = delete;

  guiContractDraw &operator=(const guiContractDraw &) = delete;

  guiContractDraw(guiContractDraw &&) = delete;

  guiContractDraw &operator=(guiContractDraw &&) = delete;
};

#endif // GUI_H
