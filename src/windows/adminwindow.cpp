#include "include/windows/adminwindow.h"
#include "ui_adminwindow.h"

AdminWindow::AdminWindow(QWidget *parent) : QMainWindow(parent)
{
    ui = std::make_unique<Ui::AdminWindow>();
    ui->setupUi(this);
}

AdminWindow::~AdminWindow() {}

Admin AdminWindow::adminstrator() const
{
    return adminstrator;
}

void AdminWindow::setAdminstrator(const Admin &value)
{
    adminstrator = value;
    emit adminstratorChanged(value);
}
