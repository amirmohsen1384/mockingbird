#include "include/core/admin.h"
#include <QFile>

Admin::Admin(QObject *parent) : Person{parent}
{}

QString Admin::absoluteAdminFile() const
{
    QDir temp = Storage::admin();
    return temp.absoluteFilePath(QString("%1.adf").arg(userName));
}

bool Admin::saveToRecord()
{
    QFile file(absoluteAdminFile());
    if(!file.open(QFile::WriteOnly))
    {
        return false;
    }
    QDataStream stream(&file);
    stream << *this;
    return true;
}
