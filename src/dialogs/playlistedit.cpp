#include "include/dialogs/playlistedit.h"
#include "include/dialogs/songedit.h"
#include "ui_playlistedit.h"
#include <QMessageBox>

void PlaylistEdit::updateModel()
{
    ui->songView->selectionModel()->clear();
    QAbstractItemModel *source = mainModel->sourceModel();
    if(source != nullptr)
    {
        updateFilter();
        updateFindCriteria();
        updateArrangeCriteria();
        ui->nameEdit->setText(source->data(QModelIndex(), Qt::DisplayRole).toString());
        setWindowTitle(QString("%1 - Playlist Editor").arg(source->data(QModelIndex(), Qt::DisplayRole).toString()));
    }
}

void PlaylistEdit::commitMetaData()
{
    mainModel->sourceModel()->setData(QModelIndex(), ui->nameEdit->text(), Qt::DisplayRole);
}

PlaylistEdit::PlaylistEdit(QWidget *parent) : QDialog(parent)
{
    ui = std::make_unique<Ui::PlaylistEdit>();
    ui->setupUi(this);

    mainModel = std::make_unique<ProxyPlaylistModel>();
    ui->songView->setModel(mainModel.get());

    connect(ui->songView->selectionModel(), &QItemSelectionModel::selectionChanged, this,
        [&](const QItemSelection &selected, const QItemSelection &deselected)
        {
            Q_UNUSED(selected)
            Q_UNUSED(deselected)
            auto indexes = ui->songView->selectionModel()->selectedIndexes();
            ui->removeButton->setDisabled(indexes.isEmpty());
        }
    );

    connect(ui->nameEdit, &QLineEdit::textChanged, this, &PlaylistEdit::commitMetaData);
    connect(ui->filterPanel, &FilterEdit::filterChanged, this, &PlaylistEdit::updateFilter);
    connect(ui->findPanel, &FindWidget::findPropertyChanged, this, &PlaylistEdit::updateFindCriteria);
    connect(ui->arrangePanel, &ArrangeWidget::sortCriteriaChanged, this, &PlaylistEdit::updateArrangeCriteria);

    ui->findPanel->setVisible(false);
    ui->filterPanel->setVisible(false);
    ui->arrangePanel->setVisible(false);
}

PlaylistEdit::~PlaylistEdit() {}

QAbstractItemModel* PlaylistEdit::model()
{
    return mainModel->sourceModel();
}

void PlaylistEdit::setModel(QAbstractItemModel* value)
{
    mainModel->setSourceModel(value);
    updateModel();
}

void PlaylistEdit::showArrangePanel(bool toggle)
{
    if(toggle)
    {
        ui->arrangePanel->setVisible(true);
        ui->findPanel->setVisible(false);
        ui->filterPanel->setVisible(false);

        ui->findButton->setChecked(false);
        ui->filterButton->setChecked(false);
    }
    else
    {
        ui->arrangePanel->setVisible(false);
    }
}

void PlaylistEdit::showFilterEdit(bool toggle)
{
    if(toggle)
    {
        ui->filterPanel->setVisible(true);
        ui->findPanel->setVisible(false);
        ui->arrangePanel->setVisible(false);

        ui->findButton->setChecked(false);
        ui->arrangeButton->setChecked(false);
    }
    else
    {
        ui->filterPanel->setVisible(false);
    }
}

void PlaylistEdit::showFindPanel(bool toggle)
{
    if(toggle)
    {
        ui->findPanel->setVisible(true);
        ui->filterPanel->setVisible(false);
        ui->arrangePanel->setVisible(false);

        ui->filterButton->setChecked(false);
        ui->arrangeButton->setChecked(false);
    }
    else
    {
        ui->findPanel->setVisible(false);
    }
}

void PlaylistEdit::addSong()
{
    SongEdit editor(this);
    if(editor.exec() == QDialog::Accepted)
    {
        PlaylistModel *target = dynamic_cast<PlaylistModel*>(mainModel->sourceModel());
        if(target != nullptr)
        {
            const Song &song = editor.getValue();
            target->appendSong(song);
        }
    }
}

void PlaylistEdit::editSong(const QModelIndex &index)
{
    const QModelIndex &target = mainModel->mapToSource(index);
    SongEdit editor(target.data(Qt::UserRole).value<Song>(), this);
    if(editor.exec() == QDialog::Accepted)
    {
        mainModel->sourceModel()->setData(target, QVariant::fromValue(editor.getValue()), Qt::UserRole);
    }
}

void PlaylistEdit::updateArrangeCriteria()
{
    if(mainModel->sourceModel() != nullptr)
    {
        ui->songView->selectionModel()->reset();
        mainModel->setSortOrder(ui->arrangePanel->getSortOrder());
        mainModel->setSortRole(ui->arrangePanel->getArrangeBase());
    }
}

void PlaylistEdit::updateFindCriteria()
{
    if(mainModel->sourceModel() != nullptr)
    {
        QRegularExpression target;
        ui->songView->selectionModel()->reset();
        Qt::MatchFlag flag = ui->findPanel->getFlag();
        switch(flag)
        {
        case Qt::MatchStartsWith:
        {
            target.setPattern(QString("^%1").arg(ui->findPanel->getText()));
            break;
        }
        case Qt::MatchEndsWith:
        {
            target.setPattern(QString("%1$").arg(ui->findPanel->getText()));
            break;
        }
        case Qt::MatchContains:
        {
            target.setPattern(QString("%1").arg(ui->findPanel->getText()));
            break;
        }
        default:
        {
            return;
        }
        }
        mainModel->setFilterRegularExpression(target);
        mainModel->setFilterRole(static_cast<int>(ui->findPanel->getSearchBase()));
        mainModel->setFilterCaseSensitivity(ui->findPanel->getCaseSensitivityMode());
    }
}

void PlaylistEdit::updateFilter()
{
    if(mainModel->sourceModel() != nullptr)
    {
        ui->songView->selectionModel()->reset();
        mainModel->setFilteringGenre(ui->filterPanel->getGenre());
        mainModel->setGenreFilteringEnabled(ui->filterPanel->isGenreFilteringEnabled());
        mainModel->setMinimumYear(ui->filterPanel->isYearFilteringEnabled() ? ui->filterPanel->getMinimumYear() : _min_year);
        mainModel->setMaximumYear(ui->filterPanel->isYearFilteringEnabled() ? ui->filterPanel->getMaximumYear() : QDate::currentDate().year());
    }
}

void PlaylistEdit::removeSong()
{
    auto indices = ui->songView->selectionModel()->selectedIndexes();

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
            QModelIndex result = mainModel->mapToSource(index);
            mainModel->sourceModel()->removeRow(result.row());
        }
    }
}
