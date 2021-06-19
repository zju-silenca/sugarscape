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
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resultPainter = new QPainter(this);
    autoPlayTimer = new QTimer(this);
    connect(autoPlayTimer, SIGNAL(timeout()), this, SLOT(on_oneDay_clicked()));
    //读取配置文件并初始化变量
    readConfig();

    //初始化生成供第一次绘制
    obj.genMap(mapNum);
    obj.genWorm(wormNum);
    obj.simulateDays(daysNum);

    obj2.map.resize(mapNum);
    obj2.worm.resize(1);
    for (int i=0; i<mapNum; i++){
        obj2.map[i].resize(mapNum);
    }
    obj2.worm[0].x = mapNum/2;
    obj2.worm[0].y = mapNum/2;
    obj2.wormCome(mapNum/2,mapNum/2,0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readConfig(){
    //读取配置文件

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

    obj.crossWayCount = setting.value("crossWayCount").toInt();

    ui->mapNum->setText(setting.value("mapNum").toString());
    ui->wormNum->setText(setting.value("wormNum").toString());
    ui->daysNum->setText(setting.value("daysNum").toString());
    ui->crossWayCount->setText(setting.value("crossWayCount").toString());
}

void MainWindow::paintEvent(QPaintEvent *event){
    drawResult();
}

void MainWindow::drawResult(){
    int Color_A;
    int RectSize = 20;//地图格子的尺寸
    QPen pointPen,pointPen2;
    pointPen.setWidth(RectSize/2);
    pointPen.setColor("green");
    pointPen2.setWidth(RectSize/2);
    pointPen2.setColor("blue");


        resultPainter->begin(this);
        for(int i = 0; i < mapNum; i++){
            for(int j = 0; j < mapNum; j++){
                //地图绘制
                resultPainter->drawRect(10+i*RectSize,60+j*RectSize,RectSize,RectSize);

                if(!ui->roadShow->isChecked()){//未选择绘制路径时
                    //糖量绘制
                    Color_A = int(obj.map[i][j].sugar)*12;
                    resultPainter->fillRect(10+i*RectSize,60+j*RectSize,RectSize,RectSize,QColor(255,0,0,Color_A));

                    //虫子绘制
                    if(obj.map[i][j].isOccupied)
                    {
                        if(obj.worm[obj.map[i][j].wormId].moveWay == 1)
                            resultPainter->setPen(pointPen2);
                        else
                            resultPainter->setPen(pointPen);
                        //resultPainter->setPen(pointPen);
                        resultPainter->drawPoint(RectSize/2+10+i*RectSize,RectSize/2+60+j*RectSize);
                        resultPainter->setPen(nullptr);
                    }
                }else{//绘制路径
                    //经过路径次数绘制
                    Color_A = int(obj2.map[i][j].sugar)*10;
                    //Color_A = int(obj2.map[i][j].sugar)*255/int(obj2.worm[0].steps+1);
                    if(Color_A > 255) Color_A = 255;
                    resultPainter->fillRect(10+i*RectSize,60+j*RectSize,RectSize,RectSize,QColor(255,0,0,Color_A));

                    //虫子绘制
                    if(obj2.map[i][j].isOccupied)
                    {
                        //pointPen.setColor("green");
                        resultPainter->setPen(pointPen);
                        resultPainter->drawPoint(RectSize/2+10+i*RectSize,RectSize/2+60+j*RectSize);
                        resultPainter->setPen(nullptr);
                    }
                }
            }
        }
        //墓地绘制
        for(int i =0; i<obj.grave.size(); i++){
            resultPainter->drawText(10,50,QString::fromLocal8Bit("墓地"));
            if(obj.grave[i].moveWay == 1)
                resultPainter->setPen(pointPen2);
            else
                resultPainter->setPen(pointPen);
            resultPainter->drawPoint(50+i*RectSize,45);
            resultPainter->setPen(nullptr);
        }

        resultPainter->end();
}


void MainWindow::on_startButton_clicked()
{
    //读取配置并判断是否合法
    if(ui->mapNum->text().toInt() <=0 ||ui->daysNum->text().toInt() <0||ui->wormNum->text().toInt() <=0
            || ui->crossWayCount->text().toInt() < 0 || ui->crossWayCount->text().toInt() > ui->wormNum->text().toInt()){
        QMessageBox::warning(this,"fail",QString::fromLocal8Bit("参数错误"));
        return;
    }
    else{
        mapNum = ui->mapNum->text().toInt();
        daysNum = ui->daysNum->text().toInt();
        wormNum = ui->wormNum->text().toInt();
        obj.crossWayCount = ui->crossWayCount->text().toInt();
    }

    //判断当前应该绘制什么
    if(!ui->roadShow->isChecked()){
        obj.resetState();
        obj.genMap(mapNum);
        obj.genWorm(wormNum);
        obj.simulateDays(daysNum);
    }else{
        obj2.resetState();
        obj2.map.resize(mapNum);
        obj2.worm.resize(1);
        for (int i=0; i<mapNum; i++){
            obj2.map[i].resize(mapNum);
        }
        obj2.worm[0].x = mapNum/2;
        obj2.worm[0].y = mapNum/2;
        obj2.wormCome(mapNum/2,mapNum/2,0);
        obj2.singleMove(daysNum);
    }
    //保存到配置文件
    QSettings setting("./config.ini",QSettings::IniFormat);
    setting.setValue("mapNum",mapNum);
    setting.setValue("wormNum",wormNum);
    setting.setValue("daysNum",daysNum);
    setting.setValue("crossWayCount",obj.crossWayCount);
    update();
}

void MainWindow::on_oneDay_clicked()
{
    //单日模拟
    if(!ui->roadShow->isChecked()){
        obj.simulateDays(1);
        daysNum++;
        ui->daysNum->setText(QString::number(daysNum));
    }else{
        obj2.singleMove(1);
        daysNum++;
        ui->daysNum->setText(QString::number(daysNum));
    }

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
    //保存数据

    QString fileName = "./result.txt";
    QFile resultFile(fileName);
    QByteArray title = "最大随机糖量 最小随机糖量 格点糖量上限 有糖格点数量 每日最低消耗 每次移动消耗 最大储存糖量 最大摄入糖量 地图大小 模拟天数 虫子数目 死亡虫子数目 加强虫子数目 死亡加强虫子数目\n";
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
    result += QString::number(obj.grave.size())+ ' ';
    result += QString::number(obj.crossWayCount) + ' ';
    int deadNum =0;
    for(int i=0; i<obj.grave.size(); i++)
        if(obj.grave[i].moveWay == 1)
            deadNum++;
    result += QString::number(deadNum) + ' ';
    resultFile.write(result.toUtf8()+'\n');


//    arr +=
//    resultFile.write();

    resultFile.close();
}


void MainWindow::on_roadShow_stateChanged(int arg1)
{
    update();
}

void MainWindow::on_saveMultyResult_clicked()
{
    int times = ui->repeatTimes->text().toInt();
    if(ui->mapNum->text().toInt() <=0 ||ui->daysNum->text().toInt() <0||ui->wormNum->text().toInt() <=0 ){
        QMessageBox::warning(this,"fail",QString::fromLocal8Bit("参数错误"));
        return;
    }
    else{
        mapNum = ui->mapNum->text().toInt();
        daysNum = ui->daysNum->text().toInt();
        wormNum = ui->wormNum->text().toInt();
    }
    if(times <= 0)
        {
            QMessageBox::warning(this,"fail",QString::fromLocal8Bit("参数错误"));
            return;
        }
    for(int i=0; i<times; i++){
        obj.resetState();
        obj.genMap(mapNum);
        obj.genWorm(wormNum);
        obj.simulateDays(daysNum);
        on_saveResult_clicked();
    }
    update();
}

void MainWindow::on_autoPlay_clicked(bool checked)
{
    int mtime = int(ui->autoTime->text().toDouble()*1000);
    if(checked)
    {
        if(mtime <= 0)
        {
            ui->autoPlay->setChecked(false);
            QMessageBox::warning(this,"fail",QString::fromLocal8Bit("参数错误"));
            return;
        }
        autoPlayTimer->start(mtime);
    }else
    {
        autoPlayTimer->stop();
    }
}
