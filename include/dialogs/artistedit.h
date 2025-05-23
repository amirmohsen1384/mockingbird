#ifndef ARTISTEDIT_H
#define ARTISTEDIT_H

#include <QDialog>

namespace Ui {
class ArtistEdit;
}

class ArtistEdit : public QDialog
{
    Q_OBJECT

public:
    explicit ArtistEdit(QWidget *parent = nullptr);
    ~ArtistEdit();

private:
    Ui::ArtistEdit *ui;
};

#endif // ARTISTEDIT_H
