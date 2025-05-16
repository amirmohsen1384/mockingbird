#include "include/windows/welcomewindow.h"
#include "ui_welcomewindow.h"
#include <QTimer>

WelcomeWindow::WelcomeWindow(QWidget *parent) : QMainWindow(parent)
{
    ui = std::make_unique<Ui::WelcomeWindow>();

    ui->setupUi(this);
    ui->continueButton->setVisible(false);

    QTimer::singleShot(2000, [&]()
    {
        ui->continueButton->setVisible(true);
    });
}

WelcomeWindow::~WelcomeWindow()
{}

void WelcomeWindow::goToSigninPage()
{
    ui->pageContainer->setCurrentWidget(ui->signinPage);
}
