#ifndef ADMIN_H
#define ADMIN_H

#include "person.h"

class Admin : public Person
{
    Q_OBJECT
public:
    explicit Admin(QObject *parent = nullptr);
    QString absoluteAdminFile() const;

public slots:
    virtual bool saveToRecord() override;

};

#endif // ADMIN_H
