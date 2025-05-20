#include "include/components/playlistview.h"
#include "ui_playlistview.h"

PlaylistView::PlaylistView(QWidget *parent) : QWidget(parent)
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

void PlaylistView::setModel(std::shared_ptr<ProxyPlaylistModel> &model)
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

void PlaylistView::updateArrangeCriteria()
{
    if(model.get() != nullptr)
    {
        model->setSortRole(static_cast<int>(ui->arrangePanel->getArrangeBase()));
    }
}

void PlaylistView::updateFindCriteria()
{
    if(model.get() != nullptr)
    {
        QRegularExpression target;
        Qt::MatchFlags flags = ui->findPanel->getFlags();
        if(flags.testFlag(Qt::MatchFlag::MatchStartsWith))
        {
            target.setPattern(QString("^%1").arg(ui->findPanel->getText()));
        }
        else if(flags.testFlag(Qt::MatchFlag::MatchEndsWith))
        {
            target.setPattern(QString("%1$").arg(ui->findPanel->getText()));
        }
        else if(flags.testFlag(Qt::MatchFlag::MatchContains))
        {
            target.setPattern(QString("%1").arg(ui->findPanel->getText()));
        }
        else if(flags.testFlag(Qt::MatchFlag::MatchFixedString))
        {
            target.setPattern(QString("%1").arg(ui->findPanel->getText()));
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
        model->setFilteringGenre(ui->filterEdit->isGenreFilteringEnabled() ? ui->filterEdit->getGenre() : Song::NoGenre);
        model->setMinimumYear(ui->filterEdit->isYearFilteringEnabled() ? ui->filterEdit->getMinimumYear() : _min_year);
        model->setMaximumYear(ui->filterEdit->isYearFilteringEnabled() ? ui->filterEdit->getMaximumYear() : QDate::currentDate().year());
    }
}

void PlaylistView::updateModel()
{
    PlaylistModel *original = dynamic_cast<PlaylistModel*>(model.get());
    ui->songView->setModel(model.get());
    if(original != nullptr)
    {
        updateFilter();
        updateFindCriteria();
        updateArrangeCriteria();
    }
}
