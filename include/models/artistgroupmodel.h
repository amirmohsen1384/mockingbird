#ifndef ARTISTGROUPMODEL_H
#define ARTISTGROUPMODEL_H

#include <QAbstractListModel>
#include <QFileSystemWatcher>
#include "include/core/artist.h"

class ArtistGroupModel : public QAbstractListModel
{
    Q_OBJECT
    QFileSystemWatcher watcher;
private:
    void updateModel();

public:
    explicit ArtistGroupModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    ArtistGroup container;
};

#endif // ARTISTGROUPMODEL_H
