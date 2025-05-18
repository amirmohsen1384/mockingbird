#include "include/models/songdelegate.h"
#include <QPainter>

QRect SongDelegate::artistRegion(const QModelIndex &index) const
{
    const QRect result = nameRegion(index);
    const QString artist = index.data(Playlist::ArtistRole).toString();
    const QRect artistRect = QFontMetrics(artistFont).boundingRect(artist);

    QPoint start = result.bottomLeft();
    start += QPoint(0, margins.bottom() + margins.top());

    return QRect(start.x(), start.y(), result.width(), artistRect.height());
}

void SongDelegate::paintArtist(QPainter *painter, const QModelIndex &index) const
{
    const QString text = index.data(Playlist::ArtistRole).toString();
    const QRect region = artistRegion(index);
    const QFont initial = painter->font();
    painter->setFont(artistFont);
    painter->drawText(region, text);
    painter->setFont(initial);
}

QRect SongDelegate::genreRegion(const QModelIndex &index) const
{
    QPoint start = nameRegion(index).topRight() + QPoint(0, margins.top() + margins.bottom());
    const QString text = index.data(Playlist::GenreRole).toString();
    const QRect genreRect = QFontMetrics(genreFont).boundingRect(text);
    const QPixmap icon = qvariant_cast<QPixmap>(index.data(Playlist::GenreIconRole));
    return QRect(
        start.x(),
        start.y(),
        genreRect.width() + icon.width() + margins.left() + margins.right(),
        std::max(icon.height(), genreRect.height())
    );
}

void SongDelegate::paintGenre(QPainter *painter, const QModelIndex &index) const
{
    QRect region = genreRegion(index);
    QString text = index.data(Playlist::GenreRole).toString();
    QPixmap icon = qvariant_cast<QPixmap>(index.data(Playlist::GenreIconRole));

    painter->save();
    painter->translate(region.topLeft());

    painter->drawPixmap(icon.rect(), icon);
    region.setTopLeft(QPoint(icon.width() + margins.left() + margins.right(), margins.top()));
    region.setWidth(region.width() - icon.width());

    const QFont initial = painter->font();
    painter->setFont(genreFont);
    painter->drawText(region, text);
    painter->setFont(initial);

    painter->restore();
}

QRect SongDelegate::coverRegion(const QModelIndex &index) const
{
    QPixmap cover = qvariant_cast<QPixmap>(index.data(Qt::DecorationRole));
    QRect rectangle = cover.rect().marginsRemoved(margins);
    rectangle.setSize(QSize(72, 72));
    return rectangle;
}

void SongDelegate::paintCover(QPainter *painter, const QModelIndex &index) const
{
    const QPixmap cover = qvariant_cast<QPixmap>(index.data(Qt::DecorationRole));
    const QRect region = coverRegion(index);

    painter->save();
    painter->setClipRegion(QRegion(region, QRegion::Ellipse));
    painter->drawPixmap(region, cover);
    painter->restore();

    QLinearGradient gradient;
    gradient.setCoordinateMode(QLinearGradient::ObjectMode);
    gradient.setStops({{0.3, Qt::blue}, {0.8, Qt::magenta}});
    gradient.setFinalStop(QPointF(0.5, 1));
    gradient.setStart(QPointF(0.5, 0));

    const QPen initial = painter->pen();
    painter->setPen(QPen(gradient, 4));

    painter->drawEllipse(region);
    painter->setPen(initial);
}

QRect SongDelegate::nameRegion(const QModelIndex &index) const
{
    const QString name = index.data().toString();
    const QString artist = index.data(Playlist::ArtistRole).toString();

    const QRect nameRect = QFontMetrics(nameFont).boundingRect(name);
    const QRect artistRect = QFontMetrics(artistFont).boundingRect(artist);

    int width = std::max(nameRect.width(), artistRect.width()) + 80;
    return QRect(0, 0, width, nameRect.height());
}
void SongDelegate::paintName(QPainter *painter, const QModelIndex &index) const
{
    const QString text = index.data().toString();
    const QFont initial = painter->font();
    const QRect region = nameRegion(index);
    painter->setFont(nameFont);
    painter->drawText(region, text);
    painter->setFont(initial);
}

SongDelegate::SongDelegate(QObject *parent) : QStyledItemDelegate{parent}
{
    genreFont.setItalic(true);
}

QSize SongDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(option.widget != nullptr ? option.widget->width() : 1000 , 72 + margins.top() * 2 + margins.bottom());
}

void SongDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
    painter->translate(option.rect.topLeft() + QPoint(margins.top(), margins.left()));
    painter->setRenderHint(QPainter::Antialiasing);

    paintCover(painter, index);
    painter->translate(coverRegion(index).width() + 20, 0);

    paintName(painter, index);

    paintArtist(painter, index);

    paintGenre(painter, index);

    painter->restore();
}
