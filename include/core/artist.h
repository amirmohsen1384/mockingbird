#ifndef ARTIST_H
#define ARTIST_H

#include "playlist.h"

class Artist : public PlaylistGroup
{
public:
    QString getName() const;
    void setName(const QString &value);

    QString getBiography() const;
    void setBiography(const QString &value);

    QPixmap getPhoto() const;
    void setPhoto(const QPixmap &value);

    bool operator==(const Artist &other) const;
    bool operator!=(const Artist &other) const;

    friend QDataStream& operator>>(QDataStream &stream, Artist &target);
    friend QDataStream& operator<<(QDataStream &stream, const Artist &target);

private:
    QString name;
    QPixmap photo;
    QString biography;
};

QDataStream& operator>>(QDataStream &stream, Artist &target);
QDataStream& operator<<(QDataStream &stream, const Artist &target);

#endif // ARTIST_H
