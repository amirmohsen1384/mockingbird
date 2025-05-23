#include "include/dialogs/artistedit.h"
#include "ui_artistedit.h"

ArtistEdit::ArtistEdit(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ArtistEdit)
{
    ui->setupUi(this);
}

ArtistEdit::~ArtistEdit()
{
    delete ui;
}
