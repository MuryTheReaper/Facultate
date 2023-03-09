#include "melodie.h"
#include <QAbstractTableModel>
#include <QBrush>
#include <QDebug>
#include <QFont>
#include <QMessageBox>
#include <vector>
class CustomTableModel : public QAbstractTableModel {
private:
  std::vector<std::pair<melodie, int>> list;

public:
  CustomTableModel(const std::vector<std::pair<melodie, int>> &list);
  int rowCount(const QModelIndex &parent = QModelIndex()) const override {
    return (int)(list.size());
  }
  int columnCount(const QModelIndex &parent = QModelIndex()) const override {
    const int col = 5;
    return col;
  }
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role) const override;
  // bool setData(const QModelIndex &index, const QVariant &value, int role)
  // override; Qt::ItemFlags flags(const QModelIndex & /*index*/) const
  // override;
  bool insertRows(int row, int count,
                  const QModelIndex &parent = QModelIndex()) override;
  bool removeRows(int row, int count,
                  const QModelIndex &parent = QModelIndex()) override;

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
  }
};
