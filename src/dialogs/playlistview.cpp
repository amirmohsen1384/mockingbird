#include "include/dialogs/playlistplayer.h"
#include "include/dialogs/playlistview.h"
#include "ui_playlistview.h"
#include <QVBoxLayout>

PlaylistView::PlaylistView(QWidget *parent) : QDialog(parent)
{
    ui = std::make_unique<Ui::PlaylistView>();
    ui->setupUi(this);

    ui->arrangePanel->setVisible(false);
    ui->filterEdit->setVisible(false);
    ui->findPanel->setVisible(false);

    connect(ui->filterEdit, &FilterEdit::filterChanged, this, &PlaylistView::updateFilter);
    connect(ui->findPanel, &FindWidget::findPropertyChanged, this, &PlaylistView::updateFindCriteria);
    connect(ui->arrangePanel, &ArrangeWidget::sortCriteriaChanged, this, &PlaylistView::updateArrangeCriteria);
}

PlaylistView::~PlaylistView()
{}

std::shared_ptr<ProxyPlaylistModel> PlaylistView::getModel()
{
    return model;
}

void PlaylistView::setModel(std::shared_ptr<ProxyPlaylistModel> model)
{
    this->model = model;
    updateModel();
}

void PlaylistView::showArrangePanel(bool toggle)
{
    if(toggle)
    {
        ui->arrangePanel->setVisible(true);
        ui->findPanel->setVisible(false);
        ui->filterEdit->setVisible(false);

        ui->findButton->setChecked(false);
        ui->filterButton->setChecked(false);
    }
    else
    {
        ui->arrangePanel->setVisible(false);
    }
}

void PlaylistView::showFilterEdit(bool toggle)
{
    if(toggle)
    {
        ui->filterEdit->setVisible(true);
        ui->findPanel->setVisible(false);
        ui->arrangePanel->setVisible(false);

        ui->findButton->setChecked(false);
        ui->arrangeButton->setChecked(false);
    }
    else
    {
        ui->filterEdit->setVisible(false);
    }

}

void PlaylistView::showFindPanel(bool toggle)
{
    if(toggle)
    {
        ui->findPanel->setVisible(true);
        ui->filterEdit->setVisible(false);
        ui->arrangePanel->setVisible(false);

        ui->filterButton->setChecked(false);
        ui->arrangeButton->setChecked(false);
    }
    else
    {
        ui->findPanel->setVisible(false);
    }
}

void PlaylistView::playSong()
{
    PlaylistPlayer player;
    player.setModel(model);
    player.exec();
}

void PlaylistView::updateArrangeCriteria()
{
    if(model.get() != nullptr)
    {
        selection->reset();
        model->setSortRole(ui->arrangePanel->getArrangeBase());
        model->setSortOrder(ui->arrangePanel->getSortOrder());
    }
}

void PlaylistView::updateFindCriteria()
{
    if(model.get() != nullptr)
    {
        selection->reset();
        QRegularExpression target;
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
        model->setFilterRegularExpression(target);
        model->setFilterRole(static_cast<int>(ui->findPanel->getSearchBase()));
        model->setFilterCaseSensitivity(ui->findPanel->getCaseSensitivityMode());
    }
}

void PlaylistView::updateFilter()
{
    if(model.get() != nullptr)
    {
        selection->reset();
        model->setFilteringGenre(ui->filterEdit->getGenre());
        model->setGenreFilteringEnabled(ui->filterEdit->isGenreFilteringEnabled());
        model->setMinimumYear(ui->filterEdit->isYearFilteringEnabled() ? ui->filterEdit->getMinimumYear() : _min_year);
        model->setMaximumYear(ui->filterEdit->isYearFilteringEnabled() ? ui->filterEdit->getMaximumYear() : QDate::currentDate().year());
    }
}

void PlaylistView::updateModel()
{
    ui->songView->setModel(model.get());
    if(model.get() != nullptr)
    {
        ui->songView->selectionModel()->reset();
        selection = ui->songView->selectionModel();

        updateFilter();
        updateFindCriteria();
        updateArrangeCriteria();

        ui->playlistTitle->setText(model->sourceModel()->data(QModelIndex(), Qt::DisplayRole).toString());
        ui->countLabel->setText(QString("%1 song(s) available in total.").arg(model->sourceModel()->rowCount()));
        setWindowTitle(QString("%1 - Playlist View").arg(model->sourceModel()->data(QModelIndex(), Qt::DisplayRole).toString()));
    }
}
