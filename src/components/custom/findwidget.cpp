#include "include/components/custom/findwidget.h"
#include "ui_findwidget.h"

FindWidget::FindWidget(QWidget *parent) : QWidget(parent), ui(new Ui::FindWidget)
{
    ui->setupUi(this);

    ui->searchModeEdit->setItemData(1, QVariant::fromValue(Qt::MatchFlag::MatchEndsWith));
    ui->searchModeEdit->setItemData(2, QVariant::fromValue(Qt::MatchFlag::MatchContains));
    ui->searchModeEdit->setItemData(0, QVariant::fromValue(Qt::MatchFlag::MatchStartsWith));
    ui->searchModeEdit->setItemData(3, QVariant::fromValue(Qt::MatchFlag::MatchFixedString));

    connect(ui->searchModeEdit, &QComboBox::currentIndexChanged, this, &FindWidget::findPropertyChanged);
    connect(ui->caseSensitivityEdit, &QCheckBox::clicked, this, &FindWidget::findPropertyChanged);
    connect(ui->searchEdit, &QLineEdit::textChanged, this, &FindWidget::findPropertyChanged);
    connect(ui->nameEdit, &QRadioButton::clicked, this, &FindWidget::findPropertyChanged);
}

FindWidget::~FindWidget()
{
    delete ui;
}

QString FindWidget::getText() const
{
    return ui->searchEdit->text();
}

Qt::MatchFlags FindWidget::getFlags() const
{
    Qt::MatchFlags result;
    result.setFlag(ui->searchModeEdit->currentData().value<Qt::MatchFlag>());
    result.setFlag(Qt::MatchFlag::MatchCaseSensitive, ui->caseSensitivityEdit->isChecked());
    return result;
}

FindWidget::Base FindWidget::getSearchBase() const
{
    return ui->nameEdit->isChecked() ? FindWidget::Name : FindWidget::Artist;
}

Qt::CaseSensitivity FindWidget::getCaseSensitivityMode()
{
    return ui->caseSensitivityEdit->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
}

void FindWidget::setText(const QString &value)
{
    ui->searchEdit->setText(value);
}

void FindWidget::setFlags(Qt::MatchFlags value)
{
    ui->caseSensitivityEdit->setChecked(value.testFlag(Qt::MatchFlag::MatchCaseSensitive));
    if(value.testFlag(Qt::MatchFlag::MatchStartsWith))
    {
        ui->searchModeEdit->setCurrentIndex(0);
    }
    else if(value.testFlag(Qt::MatchFlag::MatchEndsWith))
    {
        ui->searchModeEdit->setCurrentIndex(1);
    }
    else if(value.testFlag(Qt::MatchFlag::MatchContains))
    {
        ui->searchModeEdit->setCurrentIndex(2);
    }
    else if(value.testFlag(Qt::MatchFlag::MatchFixedString))
    {
        ui->searchModeEdit->setCurrentIndex(3);
    }

}

void FindWidget::setSearchBase(Base base)
{
    ui->artistEdit->setChecked(static_cast<int>(!base));
    ui->nameEdit->setChecked(static_cast<int>(base));
}
