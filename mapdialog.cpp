#include "mapdialog.h"
#include "ui_mapdialog.h"
#include <QMessageBox>
#include <QDebug>
#include <QSettings>


mapDialog::mapDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mapDialog)
{
    ui->setupUi(this);

    ui->maxRandS->setText(QString::number(obj.maxRandSugar));
    ui->minRandS->setText(QString::number(obj.minRandSugar));
    ui->maxStore->setText(QString::number(obj.maxStorSugar));
    ui->randCount->setText(QString::number(obj.randCount));
}

mapDialog::~mapDialog()
{
    delete ui;
}

void mapDialog::on_buttonBox_accepted()
{
    double maxRandS = ui->maxRandS->text().toDouble();
    double minRandS = ui->minRandS->text().toDouble();
    double maxStore = ui->maxStore->text().toDouble();
    int randCount = ui->randCount->text().toInt();

    if(maxRandS <= 0 || minRandS < 0 || maxRandS < minRandS || maxStore <=0 || randCount <= 0)
    {
        QMessageBox::warning(this,"fail",QString::fromLocal8Bit("参数错误"));
        return;
    }
    else{
        obj.maxRandSugar = maxRandS;
        obj.minRandSugar = minRandS;
        obj.maxStorSugar = maxStore;
        obj.randCount = randCount;
        QSettings setting("./config.ini",QSettings::IniFormat);
        setting.setValue("maxRandSugar",obj.maxRandSugar);
        setting.setValue("minRandSugar",obj.minRandSugar);
        setting.setValue("maxStorSugar",obj.maxStorSugar);
        setting.setValue("randCount",obj.randCount);
    }
}
