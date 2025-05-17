#include "include/core/artist.h"

QString Artist::getName() const
{
    return name;
}

void Artist::setName(const QString &value)
{
    name = value;
}

QString Artist::getBiography() const
{
    return biography;
}

void Artist::setBiography(const QString &value)
{
    biography = value;
}

QPixmap Artist::getPhoto() const
{
    return photo;
}

void Artist::setPhoto(const QPixmap &value)
{
    photo = value;
}

bool Artist::operator==(const Artist &other) const
{
    if(this->name != other.name)
    {
        return false;
    }
    else if(this->photo.toImage() != other.photo.toImage())
    {
        return false;
    }
    else if(this->biography != other.biography)
    {
        return false;
    }
    else if(static_cast<PlaylistGroup>(*this) != static_cast<PlaylistGroup>(other))
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Artist::operator!=(const Artist &other) const
{
    return !(*this == other);
}

QDataStream& operator>>(QDataStream &stream, Artist &target)
{
    stream >> target.name;
    stream >> target.photo;
    stream >> target.biography;
    stream >> static_cast<PlaylistGroup&>(target);
    return stream;
}

QDataStream& operator<<(QDataStream &stream, const Artist &target)
{
    stream << target.name;
    stream << target.photo;
    stream << target.biography;
    stream << static_cast<PlaylistGroup>(target);
    return stream;
}
