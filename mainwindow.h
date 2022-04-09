#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QChartView>
#include <QThread>
#include <QScatterSeries>
namespace Ui {
class MainWindow;
}
//Второй поток
class cThread: public QThread
{
    Q_OBJECT
public:
    explicit cThread(QObject *parent = nullptr);
private:
    int arrX[1];
    int arrY[1];
    QRandomGenerator random;
    void run();
signals:
    void AxisXY(int *x,int *y);
};
//Основной поток
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_pStart_clicked();
    void on_pPause_clicked();
    void on_pStop_clicked();
public slots:
    void Drow(int *x,int *y);
private:
    QChartView *chartv;
    QChart *chart;
    QValueAxis *axisx,*axisy;
    QTimer *timer;
    cThread *cthread;
    QScatterSeries *series;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
