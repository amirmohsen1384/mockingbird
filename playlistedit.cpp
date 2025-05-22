#include "playlistedit.h"
#include "ui_playlistedit.h"

void PlaylistEdit::updateModel()
{
    if(mainModel.get() != nullptr)
    {
        ui->songView->setModel(mainModel.get());
        ui->nameEdit->setText(mainModel->data(QModelIndex(), Qt::DisplayRole).toString());
        connectComponents();
    }
}

void PlaylistEdit::connectComponents()
{
    connect(selectionModel, &QItemSelectionModel::selectionChanged, this,
    [&](const QItemSelection &selected, const QItemSelection &deselected)
        {
            Q_UNUSED(deselected)
            ui->removeButton->setDisabled(selected.isEmpty());
            ui->moveUpButton->setEnabled(selected.size() == 1);
            ui->moveDownButton->setEnabled(selected.size() == 1);
        }
    );
}

PlaylistEdit::PlaylistEdit(QWidget *parent) : QWidget(parent)
{
    ui = std::make_unique<Ui::PlaylistEdit>();
    ui->setupUi(this);

    selectionModel = ui->songView->selectionModel();
}

PlaylistEdit::~PlaylistEdit() {}

std::shared_ptr<PlaylistModel> PlaylistEdit::model()
{
    return mainModel;
}

void PlaylistEdit::setModel(std::shared_ptr<PlaylistModel> value)
{
    mainModel = value;
    updateModel();
}

void PlaylistEdit::addSong()
{

}

void PlaylistEdit::removeSong()
{

}

void PlaylistEdit::moveUpSong()
{

}

void PlaylistEdit::moveDownSong()
{

}
