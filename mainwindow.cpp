#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cthread=new cThread();
    timer = new QTimer();
    chartv=new QChartView(this);
    chart=new QChart();
    axisx=new QValueAxis();
    axisy=new QValueAxis();
    ui->verticalLayout->addWidget(chartv);
    /////////////////////////
    axisx->setTitleText("X");
    chart->addAxis(axisx,Qt::AlignBottom);
    axisy->setTitleText("y");
    chart->addAxis(axisy,Qt::AlignLeft);
    ////////////////////////
    chartv->setChart(chart);
    series = new QScatterSeries();
    chartv->chart()->addSeries(series);
    chartv->chart()->createDefaultAxes();
    chartv->chart()->axisX()->setRange(0,100);
    chartv->chart()->axisY()->setRange(0,100);
    connect(cthread,SIGNAL(AxisXY(int *,int *)),this,SLOT(Drow(int *,int *)));
    connect(timer,SIGNAL(timeout()),this,SLOT(on_pStart_clicked()));

}

MainWindow::~MainWindow()
{
    cthread->exit();
    cthread->deleteLater();
    timer->deleteLater();
    chartv->deleteLater();
    chart->deleteLater();
    axisx->deleteLater();
    axisy->deleteLater();
    series->deleteLater();
    delete ui;
}

void MainWindow::on_pStart_clicked()
{
    ui->pStart->setEnabled(false);
    if(ui->pStart->isEnabled()==false)
    {
        timer->start(5000);
        cthread->start();
    }
}

void MainWindow::on_pPause_clicked()
{
    ui->pStart->setEnabled(true);
    timer->stop();
}

void MainWindow::on_pStop_clicked()
{
    ui->pStart->setEnabled(true);
    timer->stop();
    series->clear();
}

void MainWindow::Drow(int *x,int *y)
{
    series->append(*x, *y);
}
cThread::cThread(QObject *parent):QThread (parent)
{}

void cThread::run()
{
    arrX[0]=random.global()->bounded(0,100);
    arrY[0]=random.global()->bounded(0,100);
    emit AxisXY(arrX,arrY);
}
