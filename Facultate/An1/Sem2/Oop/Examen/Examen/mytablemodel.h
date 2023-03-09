#include "muzica.h"
#include <QAbstractTableModel>
#include <QBrush>
#include <QDebug>
#include <QFont>
#include <QMessageBox>
#include <vector>
class CustomTableModel : public QAbstractTableModel {
private:
  // tabelul are o lista de perechi melodie, int
  //  unde int este nr de melodii cu acelasi rank
  std::vector<std::pair<melodie, int>> list;

public:
  // constructor
  CustomTableModel(const std::vector<std::pair<melodie, int>> &list);

  // initialiam nr de linii cu cate melodii avem
  int rowCount(const QModelIndex &parent = QModelIndex()) const override {
    return (int)(list.size());
  }

  // initializam nr de coloane cu 5 (id, titlu, artist, rank, egal)
  int columnCount(const QModelIndex &parent = QModelIndex()) const override {
    const int col = 5;
    return col;
  }

  // functie suprascrisa pentru a modifica cum si ce arata tabelul
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  // functie care defineste capul tabelului
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role) const override;

  // functie care adauga linii in tabel
  bool insertRows(int row, int count,
                  const QModelIndex &parent = QModelIndex()) override;

  // functie care eleminit linii din tabel
  bool removeRows(int row, int count,
                  const QModelIndex &parent = QModelIndex()) override;

  // functie care modifica tabelul
  void setlist(const std::vector<std::pair<melodie, int>> &list) {
    if (rowCount() > list.size()) {
      this->removeRows((int)list.size(), rowCount() - (int)list.size());
    } else if (rowCount() < list.size()) {
      this->insertRows(rowCount(), (int)list.size() - rowCount());
    }
    this->list = list;
    auto topLeft = createIndex(0, 0);
    auto bottomR = createIndex(rowCount(), columnCount());
    emit dataChanged(topLeft, bottomR);
    emit layoutChanged();
  }
};
