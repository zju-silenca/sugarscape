#ifndef MAPDIALOG_H
#define MAPDIALOG_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class mapDialog;
}

class mapDialog : public QDialog,public MainWindow::Qtapi
{
    Q_OBJECT

public:
    explicit mapDialog(QWidget *parent = nullptr);
    ~mapDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::mapDialog *ui;
};

#endif // MAPDIALOG_H
