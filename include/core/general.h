#ifndef GENERAL_H
#define GENERAL_H

#include <QDir>
#include <QApplication>

namespace Storage
{
    QDir root();
    QDir user();
    QDir admin();
    QDir songs();
}

#endif // GENERAL_H
