#ifndef CHART_H
#define CHART_H

#include <QtCharts>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QTimer>
#include "QDateTime"
#include <QWidget>

class Chart : public QWidget
{
    Q_OBJECT
public:
    explicit Chart(QWidget *parent = nullptr);
    void init_chart(QString title = tr("无线传输模块调试"), qint16 min =0 ,qint16 max= 30000);//表格初始化
    void draw_line(QDateTime current_time, double number);//画线
    ~Chart();

private slots:

    void save(QDateTime start_time,QDateTime end_time);//保存图表
private:
    QTimer *timer;                           //计时器
    QChartView *chartView;
    QChart *chart;                           //画布
    QSplineSeries *series;                     //线
    QDateTimeAxis *axisX;                    //轴
    QValueAxis *axisY;
};

#endif // CHART_H
