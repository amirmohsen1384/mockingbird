#include "include/windows/adminwindow.h"
#include "ui_adminwindow.h"
#include <QMessageBox>
#include <exception>

AdminWindow::AdminWindow(const Admin &admin, QWidget *parent) : AdminWindow(parent)
{
    setAdminstrator(admin);
}

AdminWindow::AdminWindow(QWidget *parent) : QMainWindow(parent)
{
    ui = std::make_unique<Ui::AdminWindow>();
    ui->setupUi(this);
}

AdminWindow::~AdminWindow() {}

Admin AdminWindow::adminstrator() const
{
    return admin;
}

void AdminWindow::updateMetaData()
{
    ui->adminNameLabel->setText(admin.getFullName());
    ui->firstNameEdit->setText(admin.getFirstName());
    ui->lastNameEdit->setText(admin.getLastName());
    ui->userNameEdit->setText(admin.getUserName());
    ui->passwordEdit->setText(admin.getPassword());
}

void AdminWindow::setAdminstrator(const Admin &value)
{
    admin = value;
    updateMetaData();
    emit adminstratorChanged(value);
}

void AdminWindow::rejectChanging()
{
    ui->pageContainer->setCurrentWidget(ui->mainPage);
    updateMetaData();
}

void AdminWindow::acceptChanging()
{
    try
    {
        const QString firstName = ui->firstNameEdit->text();
        const QString lastName = ui->lastNameEdit->text();
        const QString userName = ui->userNameEdit->text();
        const QString password = ui->passwordEdit->text();

        QRegularExpression pattern("[a-zA-Z ]{1,}");
        if(!pattern.match(firstName).hasMatch())
        {
            throw std::runtime_error("The first name should only contain non-letter characters and not be empty.");
        }
        else if(!pattern.match(lastName).hasMatch())
        {
            throw std::runtime_error("The last name should only contain non-letter characters and not be empty.");
        }

        pattern.setPattern(".{6,}");
        if(!pattern.match(userName).hasMatch())
        {
            throw std::runtime_error("The user name should have at least 6 characters.");
        }

        pattern.setPattern("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[\\W_])[A-Za-z\\d\\W_]{8,}$");
        if(!pattern.match(password).hasMatch())
        {
            throw std::runtime_error("A strong password is at least 8 character, and has all kinds of characters.");
        }

        admin.setFirstName(firstName);
        admin.setLastName(lastName);
        admin.setUserName(userName);
        admin.setPassword(password);
    }
    catch(std::exception &e)
    {
        QMessageBox::critical(this, "Error", e.what());
        return;
    }

    if(admin.saveToRecord())
    {
        updateMetaData();
    }
    ui->pageContainer->setCurrentWidget(ui->mainPage);
}

void AdminWindow::togglePasswordShow(bool toggle)
{
    if(!toggle)
    {
        ui->passwordEdit->setEchoMode(QLineEdit::EchoMode::Password);
        ui->showPasswordButton->setIcon(QIcon(":/images/windows/show-password.png"));
    }
    else
    {
        ui->passwordEdit->setEchoMode(QLineEdit::Normal);
        ui->showPasswordButton->setIcon(QIcon(":/images/windows/hide-password.png"));
    }
}

void AdminWindow::goToInfoChangingMode()
{
    ui->pageContainer->setCurrentWidget(ui->informationPage);
}
