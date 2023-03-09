#include "myTableModel.h"

using namespace std;
CustomTableModel::CustomTableModel(
    const std::vector<std::pair<melodie, int>> &list)
    : list{list} {}
QVariant CustomTableModel::data(const QModelIndex &index, int role) const {
  int row = index.row();
  int col = index.column();
  // const int maxi = 300;

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
  /* if (role == Qt::FontRole) {
     if (col == 0) { // change font only for cell(0,x)
       QFont boldFont;
       boldFont.setBold(true);
       return boldFont;
     }
   }
   if (role == Qt::BackgroundRole) {
     if (col == 3 &&
         list[row].get_ore() > maxi) // change background only for cell(1,2)
       return QBrush(Qt::red);
   }*/
  /*if (role == Qt::TextAlignmentRole) {
    if (row == 1 && col == 1) // change text alignment only for cell(1,1)
      return int(Qt::AlignRight | Qt::AlignVCenter);
  }
  if (role == Qt::CheckStateRole) {
    if (row == 1 && col == 0) // add a checkbox to cell(1,0)
      return Qt::Checked;
  }*/
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
