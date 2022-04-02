#ifndef WIDGET_H
#define WIDGET_H

#include <QtSerialPort>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QTimer>
#include "QDateTime"
#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include "chart.h"
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);

    ~Widget();
private slots:
    void port_handle(int);//端口号函数
    void baud_handle(int);//波特率函数
    void start_collect();
    void end_collect();
    void on_readyRead();
private:
    QComboBox *port;//串口号
    QComboBox *baud;//波特率
    QPushButton *start;//开始采集
    QPushButton *end;//结束采集
    QByteArray buff;//缓冲区
    QTimer *timer;//计时器
    Chart *chart;//绘图
    QSerialPort global_port;//
};

#endif // WIDGET_H
