#include "mainwindow.h"
#include "mapdialog.h"
#include "wormdialog.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMessageBox>
#include <QColor>
#include <QtDebug>
#include <QPen>
#include <QFileDialog>
#include <QTextCodec>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resultPainter = new QPainter(this);

    readConfig();
    obj.genMap(mapNum);
    obj.genWorm(wormNum);
    obj.simulateDays(daysNum);
    //QTextCodec* codec = QTextCodec::codecForName("GB2312");
//    connect(this,SIGNAL(on_startButton_clicked()),this,SLOT(paintEvent()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readConfig(){
    QSettings setting("./config.ini",QSettings::IniFormat);

    mapNum = setting.value("mapNum").toInt();
    wormNum = setting.value("wormNum").toInt();
    daysNum = setting.value("daysNum").toInt();

    obj.maxRandSugar = setting.value("maxRandSugar").toDouble();
    obj.minRandSugar = setting.value("minRandSugar").toDouble();
    obj.maxStorSugar = setting.value("maxStorSugar").toDouble();
    obj.randCount = setting.value("randCount").toInt();

    obj.minConsum = setting.value("minConsum").toDouble();
    obj.moveConsum = setting.value("moveConsum").toDouble();
    obj.maxSugar = setting.value("maxSugar").toDouble();
    obj.dayMaxSugar = setting.value("dayMaxSugar").toDouble();

    ui->mapNum->setText(setting.value("mapNum").toString());
    ui->wormNum->setText(setting.value("wormNum").toString());
    ui->daysNum->setText(setting.value("daysNum").toString());
}

void MainWindow::paintEvent(QPaintEvent *event){
    drawResult();
}

void MainWindow::drawResult(){
    int Color_A;
    int RectSize = 20;//地图格子的尺寸
    QPen pointPen;
    pointPen.setWidth(RectSize/2);
    pointPen.setColor("green");


        resultPainter->begin(this);
        for(int i = 0; i < mapNum; i++){
            for(int j = 0; j < mapNum; j++){
                //地图绘制
                resultPainter->drawRect(10+i*RectSize,60+j*RectSize,RectSize,RectSize);
                //糖量绘制
                Color_A = int(obj.map[i][j].sugar)*12;
                resultPainter->fillRect(10+i*RectSize,60+j*RectSize,RectSize,RectSize,QColor(255,0,0,Color_A));
                //虫子绘制
                if(obj.map[i][j].isOccupied)
                {
                    resultPainter->setPen(pointPen);
                    resultPainter->drawPoint(RectSize/2+10+i*RectSize,RectSize/2+60+j*RectSize);
                    resultPainter->setPen(nullptr);
                }
            }
        }
        //墓地绘制
        for(int i =0; i<obj.grave.size(); i++){
            resultPainter->drawText(10,50,QString::fromLocal8Bit("墓地"));
            resultPainter->setPen(pointPen);
            resultPainter->drawPoint(50+i*RectSize,45);
            resultPainter->setPen(nullptr);
        }

        resultPainter->end();
}


void MainWindow::on_startButton_clicked()
{
    if(ui->mapNum->text().toInt() <=0 ||ui->daysNum->text().toInt() <0||ui->wormNum->text().toInt() <=0 ){
        QMessageBox::warning(this,"fail",QString::fromLocal8Bit("参数错误"));
        return;
    }
    else{
        mapNum = ui->mapNum->text().toInt();
        daysNum = ui->daysNum->text().toInt();
        wormNum = ui->wormNum->text().toInt();
    }
    obj.resetState();
    obj.genMap(mapNum);
    obj.genWorm(wormNum);
    obj.simulateDays(daysNum);

    QSettings setting("./config.ini",QSettings::IniFormat);
    setting.setValue("mapNum",mapNum);
    setting.setValue("wormNum",wormNum);
    setting.setValue("daysNum",daysNum);
    update();
}

void MainWindow::on_oneDay_clicked()
{
    obj.simulateDays(1);
    daysNum++;
    ui->daysNum->setText(QString::number(daysNum));
    update();
}

void MainWindow::on_mapGen_triggered()
{
    QDialog *d = new mapDialog(this);
    d->show();
}

void MainWindow::on_wormGen_triggered()
{
    QDialog *d = new wormDialog(this);
    d->show();
}


void MainWindow::on_saveResult_clicked()
{
    QString fileName = "./result.txt";
    QFile resultFile(fileName);
    QByteArray title = "最大随机糖量 最小随机糖量 格点糖量上限 有糖格点数量 每日最低消耗 每次移动消耗 最大储存糖量 最大摄入糖量 地图大小 模拟天数 虫子数目 死亡虫子数目\n";
    if(!resultFile.exists()){
        resultFile.open(QIODevice::WriteOnly | QIODevice::Append);
        resultFile.write(title);
        resultFile.close();
    }
    resultFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QString result = QString::number(obj.maxRandSugar,'f',3) + ' ';
    result += QString::number(obj.minRandSugar,'f',3) + ' ';
    result += QString::number(obj.maxStorSugar,'f',3) + ' ';
    result += QString::number(obj.randCount) + ' ';
    result += QString::number(obj.minConsum,'f',3) + ' ';
    result += QString::number(obj.moveConsum,'f',3) + ' ';
    result += QString::number(obj.maxSugar,'f',3) + ' ';
    result += QString::number(obj.dayMaxSugar,'f',3) + ' ';
    result += QString::number(mapNum) + ' ';
    result += QString::number(daysNum) + ' ';
    result += QString::number(wormNum) + ' ';
    result += QString::number(obj.grave.size());
    resultFile.write(result.toUtf8()+'\n');


//    arr +=
//    resultFile.write();

    resultFile.close();
}
