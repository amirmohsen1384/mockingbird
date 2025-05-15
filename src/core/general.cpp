#include "include/core/general.h"

QDir Storage::root()
{
    const QString name = QApplication::applicationName();
    QDir result = QDir::temp();
    result.mkdir(name);
    result.cd(name);
    return result;
}

QDir Storage::admin()
{
    const QString name = "Admins";
    QDir result = root();
    result.mkdir(name);
    result.cd(name);
    return result;
}

QDir Storage::user()
{
    const QString name = "Users";
    QDir result = root();
    result.mkdir(name);
    result.cd(name);
    return result;
}
