﻿#include "wormdialog.h"
#include "ui_wormdialog.h"
#include <QMessageBox>
#include <QSettings>

wormDialog::wormDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::wormDialog)
{
    ui->setupUi(this);

    ui->minConsum->setText(QString::number(obj.minConsum));
    ui->moveConsum->setText(QString::number(obj.moveConsum));
    ui->maxSugar->setText(QString::number(obj.maxSugar));
    ui->dayMaxSugar->setText(QString::number(obj.dayMaxSugar));
}

wormDialog::~wormDialog()
{
    delete ui;
}

void wormDialog::on_buttonBox_accepted()
{
    double minConsum = ui->minConsum->text().toDouble();
    double moveConsum = ui->moveConsum->text().toDouble();
    double maxSugar = ui->maxSugar->text().toDouble();
    double dayMaxSugar = ui->dayMaxSugar->text().toInt();

    if(minConsum < 0 || moveConsum < 0 || maxSugar <=0 || dayMaxSugar <= 0)
    {
        QMessageBox::warning(this,"fail",QString::fromLocal8Bit("参数错误"));
        return;
    }
    else{
        obj.minConsum = minConsum;
        obj.moveConsum = moveConsum;
        obj.maxSugar = maxSugar;
        obj.dayMaxSugar = dayMaxSugar;
        QSettings setting("./config.ini",QSettings::IniFormat);
        setting.setValue("minConsum",obj.minConsum);
        setting.setValue("moveConsum",obj.moveConsum);
        setting.setValue("maxSugar",obj.maxSugar);
        setting.setValue("dayMaxSugar",obj.dayMaxSugar);
    }
}
