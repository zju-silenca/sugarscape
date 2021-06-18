#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "src/sugarscape.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow ,public Qtapi
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    virtual void paintEvent(QPaintEvent *event);
    void drawResult();


    ~MainWindow();

private slots:

    void on_startButton_clicked();

    void on_oneDay_clicked();

    void on_mapGen_triggered();

    void on_wormGen_triggered();

    void on_saveResult_clicked();

    void on_roadShow_stateChanged(int arg1);

    void on_saveMultyResult_clicked();

private:
    Ui::MainWindow *ui;
    int testNum,mapNum,wormNum,daysNum;
    void readConfig();

    QPainter *resultPainter;
};
#endif // MAINWINDOW_H
