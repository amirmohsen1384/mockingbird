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

constexpr int _min_year = 1900;

#endif // GENERAL_H
