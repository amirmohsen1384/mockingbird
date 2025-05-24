#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include "include/core/admin.h"

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit AdminWindow(const Admin &admin, QWidget *parent = nullptr);
    ~AdminWindow();

    Admin adminstrator() const;

public slots:
    void setAdminstrator(const Admin &value);

signals:
    void adminstratorChanged(const Admin &value);

private:
    Admin adminstrator;
    std::unique_ptr<Ui::AdminWindow> ui;
};

#endif // ADMINWINDOW_H
