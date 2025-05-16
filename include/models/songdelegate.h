#ifndef SONGDELEGATE_H
#define SONGDELEGATE_H

#include <QStyledItemDelegate>
#include "include/models/playlistmodel.h"

class SongDelegate : public QStyledItemDelegate
{
    Q_OBJECT
    QMargins margins = QMargins(5, 5, 5, 5);
    QFont yearFont = QFont("Segoe UI", 10);
    QFont genreFont = QFont("Segoe UI", 12);
    QFont artistFont = QFont("Segoe UI", 10, QFont::Bold);
    QFont nameFont = QFont("Segoe Print", 14, QFont::Bold);

private:
    QRect majorInfoRegion(const QModelIndex &index) const;
    QRect minorInfoRegion(const QModelIndex &index) const;
    QRect artistRegion(const QModelIndex &index) const;
    QRect coverRegion(const QModelIndex &index) const;
    QRect nameRegion(const QModelIndex &index) const;

public:
    SongDelegate(QObject *parent = nullptr);

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};
#endif // SONGDELEGATE_H
