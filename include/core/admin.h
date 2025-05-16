#ifndef ADMIN_H
#define ADMIN_H

#include "person.h"

class Admin : public Person
{
public:
    QString absoluteAdminFile() const;
    virtual bool saveToRecord() override;
};

#endif // ADMIN_H
