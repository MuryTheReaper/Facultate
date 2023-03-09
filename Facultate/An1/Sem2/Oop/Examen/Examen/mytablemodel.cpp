#include "mytablemodel.h"

using namespace std;
CustomTableModel::CustomTableModel(
    const std::vector<std::pair<melodie, int>> &list)
    : list{list} {}
QVariant CustomTableModel::data(const QModelIndex &index, int role) const {
  int row = index.row();
  int col = index.column();

  if (role == Qt::DisplayRole) {
    if (col == 0) {
      return QString::fromStdString(to_string(list[row].first.getId()));
    } else if (col == 1) {
      return QString::fromStdString(list[row].first.getTitlu());
    } else if (col == 2) {
      return QString::fromStdString(list[row].first.getArtist());
    } else if (col == 3) {
      return QString::fromStdString(to_string(list[row].first.getRank()));
    } else if (col == 4) {
      return QString::fromStdString(to_string(list[row].second));
    }
  }

  return QVariant();
}

QVariant CustomTableModel::headerData(int section, Qt::Orientation orientation,
                                      int role) const {
  if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
    switch (section) {
    case 0:
      return QString("Id");
    case 1:
      return QString("Titilu");
    case 2:
      return QString("Artist");
    case 3:
      return QString("Rank");
    case 4:
      return QString("Egal");
    default:
      return QString("EXTRA");
    }
  }
  return QVariant();
}
bool CustomTableModel::insertRows(int row, int count,
                                  const QModelIndex &parent) {
  beginInsertRows(parent, row, row + count - 1);
  endInsertRows();
  return true;
}
bool CustomTableModel::removeRows(int row, int count,
                                  const QModelIndex &parent) {
  beginRemoveRows(parent, row, row + count - 1);
  endRemoveRows();
  return true;
}
