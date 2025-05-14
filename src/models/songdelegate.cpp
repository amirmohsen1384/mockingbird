#include "include/models/songdelegate.h"
#include <QPainter>

QRect SongDelegate::majorInfoRegion(const QModelIndex &index) const
{
    const QString name = index.data().toString();
    const QString artist = index.data(Qt::ToolTipRole).toString();

    QFontMetrics nameFontMetrics(nameFont);
    const QRect nameRect = nameFontMetrics.boundingRect(name);

    QFontMetrics artistFontMetrics(artistFont);
    const QRect artistRect = artistFontMetrics.boundingRect(artist);

    int width = std::max(nameRect.width(), artistRect.width());
    width += 50;

    QRect result;
    result.setWidth(width);
    result.setTopLeft(QPoint(0, 0));
    result.setHeight(nameRect.height() + margins.bottom() + margins.top() + artistRect.height());

    return result;
}

QRect SongDelegate::minorInfoRegion(const QModelIndex &index) const
{
    QRect result = majorInfoRegion(index);
    const int height = result.height();

    result.setTopLeft(result.topRight());
}

QRect SongDelegate::artistRegion(const QModelIndex &index) const
{
    QFontMetrics artistFontMetrics(artistFont);
    const QRect majorRegion = majorInfoRegion(index);

    const QString artist = index.data(Qt::ToolTipRole).toString();
    const QRect artistRect = artistFontMetrics.boundingRect(artist);

    QRect result = artistRect;
    QRect nameRect = nameRegion(index);
    QPoint start = nameRect.bottomLeft();
    start += QPoint(0, margins.bottom() + margins.top());

    result.setTopLeft(start);
    result.setWidth(majorRegion.width());

    return result;
}

QRect SongDelegate::coverRegion(const QModelIndex &index) const
{
    const QPixmap cover = QPixmap(":/images/playlist/song.png");
    QRect region = cover.rect().marginsAdded(margins);
    region.setTopLeft(QPoint(0, 0));
    return region;
}

QRect SongDelegate::nameRegion(const QModelIndex &index) const
{
    QFontMetrics nameFontMetrics(nameFont);
    const QString name = index.data().toString();

    QRect nameRect = nameFontMetrics.boundingRect(name);
    nameRect.setWidth(majorInfoRegion(index).width());

    return nameRect;
}

SongDelegate::SongDelegate(QObject *parent) : QStyledItemDelegate{parent}
{
    genreFont.setItalic(true);
}

QSize SongDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{

}

void SongDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
    const int margin = 5;

    const QPixmap logo = qvariant_cast<QPixmap>(index.data(Qt::DecorationRole));

    painter->save();
    painter->setClipRegion(QRegion(logo.rect(), QRegion::Ellipse));

    painter->drawPixmap(QPoint(0, 0), logo);
    painter->restore();

    QLinearGradient gradient;
    gradient.setCoordinateMode(QLinearGradient::ObjectMode);
    gradient.setStops({{0.5, Qt::blue}, {1.0, Qt::green}});
    gradient.setFinalStop(QPointF(0.5, 1));
    gradient.setStart(QPointF(0.5, 0));

    {
        const QPen initial = painter->pen();
        painter->setPen(QPen(gradient, 2));
        painter->drawEllipse(logo.rect());
        painter->setPen(initial);
    }

    painter->translate(logo.rect().width() + margin, 0);

    {
        const QFont initial = painter->font();

        painter->setFont(QFont("Segoe Print", 14));
        painter->drawText(QPoint(0, 0), index.data(Qt::DisplayRole).toString());

        painter->setFont(QFont("Segoe UI", 10, QFont::Bold));
        painter->drawText(QPoint(0, margin * 2), QString("A Song By %1").arg(index.data(PlaylistRole::ArtistRole).toString()));

        painter->setFont(initial);
    }
    painter->restore();
}
