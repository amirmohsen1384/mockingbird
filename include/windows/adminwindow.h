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
    explicit AdminWindow(QWidget *parent = nullptr);
    ~AdminWindow();

    Admin adminstrator() const;

private slots:
    void updateMetaData();
    void rejectChanging();
    void acceptChanging();
    void togglePasswordShow(bool toggle);

public slots:
    void setAdminstrator(const Admin &value);
    void goToInfoChangingMode();

signals:
    void adminstratorChanged(const Admin &value);

private:
    Admin admin;
    std::unique_ptr<Ui::AdminWindow> ui;
};

#endif // ADMINWINDOW_H
