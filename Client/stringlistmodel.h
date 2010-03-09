/*
 * Stringlistmodel class
 *
 * @author      Toni Jussila <toni.jussila@fudeco.com>
 * @copyright   (c) 2010 Speed Freak team
 * @license     http://opensource.org/licenses/gpl-license.php GNU Public License
 * @exaple      http://qt.nokia.com/doc/4.0/qt4-interview.html#example-code
 */

#ifndef STRINGLISTMODEL_H
#define STRINGLISTMODEL_H
#include <QAbstractListModel>
#include <QObject>
#include <QStringList>

class StringListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    StringListModel(const QStringList &strings, QObject *parent = 0):QAbstractListModel(parent), stringList(strings) {}
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

private:
    QStringList stringList;
};

#endif // STRINGLISTMODEL_H
