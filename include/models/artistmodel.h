#ifndef ARTISTMODEL_H
#define ARTISTMODEL_H

#include <QAbstractListModel>
#include "include/core/artist.h"

class ArtistModel : public QAbstractListModel
{
    Q_OBJECT
public:
    Q_DISABLE_COPY_MOVE(ArtistModel)

    ArtistModel(QObject *parent) : QAbstractListModel(parent) {}
    ~ArtistModel() {}

    const Artist& artist() const;

    bool insertRows(int row, int count, const QModelIndex &parent) override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public slots:
    void insertPlaylist(int row, const Playlist &target);
    void insertPlaylist(int row, const PlaylistGroup &target);

    void prependPlaylist(const Playlist &target);
    void prependPlaylist(const PlaylistGroup &target);

    void appendPlaylist(const Playlist &target);
    void appendPlaylist(const PlaylistGroup &target);

    void removePlaylist(int row);

    void setName(const QString &value);
    void setPhoto(const QPixmap &value);
    void setBiography(const QString &value);

private:
    Artist container;
};

#endif // ARTISTMODEL_H
