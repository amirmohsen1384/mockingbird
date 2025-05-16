#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H

#include <QMainWindow>

namespace Ui {
class WelcomeWindow;
}

class WelcomeWindow : public QMainWindow
{
    Q_OBJECT

public:
    Q_DISABLE_COPY_MOVE(WelcomeWindow)
    explicit WelcomeWindow(QWidget *parent = nullptr);
    ~WelcomeWindow();

public slots:
    void goToSigninPage();

private:
    std::unique_ptr<Ui::WelcomeWindow> ui;
};

#endif // WELCOMEWINDOW_H
