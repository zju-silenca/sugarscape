#ifndef WORMDIALOG_H
#define WORMDIALOG_H
#include "mainwindow.h"
#include <QDialog>

namespace Ui {
class wormDialog;
}

class wormDialog : public QDialog,public Qtapi
{
    Q_OBJECT

public:
    explicit wormDialog(QWidget *parent = nullptr);
    ~wormDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::wormDialog *ui;
};

#endif // WORMDIALOG_H
