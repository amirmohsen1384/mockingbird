#include "playlistedit.h"
#include "ui_playlistedit.h"
#include <QMessageBox>
#include "playlistedit.h"
#include "ui_playlistedit.h"
#include "include/dialogs/songedit.h"

void PlaylistEdit::updateModel()
{
    if(mainModel.get() != nullptr)
    {
        ui->songView->setModel(mainModel.get());
        selectionModel = ui->songView->selectionModel();
        ui->nameEdit->setText(mainModel->data(QModelIndex(), Qt::DisplayRole).toString());
        setWindowTitle(QString("%1 - Playlist Editor").arg(mainModel->data(QModelIndex(), Qt::DisplayRole).toString()));
        connectComponents();
    }
}

void PlaylistEdit::connectComponents()
{
    connect(selectionModel, &QItemSelectionModel::selectionChanged, this,
    [&](const QItemSelection &selected, const QItemSelection &deselected)
        {
            Q_UNUSED(selected)
            Q_UNUSED(deselected)
            auto indexes = ui->songView->selectionModel()->selectedIndexes();
            ui->removeButton->setDisabled(indexes.isEmpty());
        }
    );
}

PlaylistEdit::PlaylistEdit(QWidget *parent) : QWidget(parent)
{
    ui = std::make_unique<Ui::PlaylistEdit>();
    ui->setupUi(this);
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
    SongEdit editor(this);
    if(editor.exec() == QDialog::Accepted)
    {
        mainModel->appendSong(editor.getValue());
    }
}

void PlaylistEdit::editSong(const QModelIndex &index)
{
    SongEdit editor(index.data(Qt::UserRole).value<Song>(), this);
    if(editor.exec() == QDialog::Accepted)
    {
        mainModel->setData(index, QVariant::fromValue(editor.getValue()), Qt::UserRole);
    }
}

void PlaylistEdit::removeSong()
{
    auto indices = selectionModel->selectedIndexes();

    QMessageBox message;
    message.setWindowTitle("Confirm");
    message.setIcon(QMessageBox::Warning);
    message.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    message.setText(QString("Are you sure to remove %1 song(s) permanently?").arg(indices.size()));
    if(message.exec() == QMessageBox::Yes)
    {
        std::sort(indices.begin(), indices.end(),
            [&](const QModelIndex &one, const QModelIndex &two)
            {
                return one.row() >= two.row();
            }
        );
        for(const QModelIndex &index : indices)
        {
            mainModel->removeSong(index.row());
        }
    }
}
