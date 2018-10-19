#include "MyFileSystemModel.h"
#include <QtDebug>

MyFileSystemModel::MyFileSystemModel(QObject *parent) :
    QFileSystemModel(parent)
{

}

QVariant MyFileSystemModel::data(const QModelIndex &index, int role) const
{
    switch (role)
    {
    case Qt::TextAlignmentRole:
        switch (index.column()) {
        case 1:
            return (qint32)(Qt::AlignVCenter | Qt::AlignRight);
        default:
            break;
        }
        break;
    default:
        break;
    }
    return QFileSystemModel::data(index, role);
}

QVariant MyFileSystemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch (role)
    {
    case Qt::DisplayRole:
    {
        QString strText;
        switch (section) {
        case 0:
            strText = "名称";
            break;
        case 1:
            strText = "大小";
            break;
        case 2:
            strText = "类型";
            break;
        case 3:
            strText = "修改日期";
            break;
        default:
            break;
        }
        return strText;
    }
    default:
        break;
    }
    return QFileSystemModel::headerData(section, orientation, role);
}

void MyFileSystemModel::sort(int column, Qt::SortOrder order)
{
    //qDebug() << QString("Sort: column = %1, order = %2").arg(column).arg(order);
    QFileSystemModel::sort(column, order);
}
