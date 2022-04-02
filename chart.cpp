#include "chart.h"

Chart::Chart(QWidget *parent): QWidget(parent)
{
    timer = new QTimer(this);
    timer->start();
    timer->setInterval(1000);    //设置定时周期//创建定时器
}
void Chart::init_chart(QString title, qint16 min,qint16 max)
{
    QPen penY(Qt::darkBlue,3,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
    chartView = new QChartView(this);
    chartView->resize(1600,1000);
    chart = new QChart();
    chart->setTitle(title);
    series = new QSplineSeries;
    axisX = new QDateTimeAxis();
    axisY = new QValueAxis();
    chart->legend()->hide();                             //隐藏图例
    chart->addSeries(series);                            //把线添加到chart
    chart->setTheme(QChart::ChartThemeDark);
    axisX->setTickCount(10);                             //设置坐标轴格数
    axisY->setTickCount(5);
    axisX->setFormat("hh:mm:ss");                        //设置时间显示格式
    axisY->setMin(min);                                    //设置Y轴范围
    axisY->setMax(max);
    axisX->setTitleText("实时时间");                       //设置X轴名称
    axisY->setLinePenColor(QColor(Qt::darkBlue));        //设置坐标轴颜色样式
    axisY->setGridLineColor(QColor(Qt::darkBlue));
    axisY->setGridLineVisible(true);                    //设置Y轴网格显示
    axisY->setLinePen(penY);
    axisX->setLinePen(penY);
    chart->addAxis(axisX,Qt::AlignBottom);               //设置坐标轴位于chart中的位置
    chart->addAxis(axisY,Qt::AlignLeft);
    series->attachAxis(axisX);                           //把数据添加到坐标轴上
    series->attachAxis(axisY);
    axisY->setTitleText("y");
    //把chart显示到窗口上
    chartView->setChart(chart);
    //chartView->setRenderHint(QPainter::Antialiasing);   //设置抗锯齿
}

void Chart::draw_line(QDateTime current_time, double number)
{
    //设置坐标轴显示范围
    chart->axisX()->setMin(QDateTime::currentDateTime().addSecs(-60 * 1));       //系统当前时间的前一秒
    chart->axisX()->setMax(QDateTime::currentDateTime().addSecs(0));            //系统当前时间                        //这里生成随机数做测试
    //增加新的点到曲线末端
    series->append(current_time.toMSecsSinceEpoch(), number);
}

void Chart::save(QDateTime start_time,QDateTime end_time)
{
    chart->axisX()->setMin(start_time);
    chart->axisX()->setMax(end_time);
    QPixmap p = chartView->grab();
    QImage image = p.toImage();
    QString filename = QFileDialog::getSaveFileName(this,
        tr("Save Image"),
        "",
        tr("*.bmp;; *.png;; *.jpg;; *.tif;; *.GIF")); //选择路径
    if (filename.isEmpty())
    {
        return;
    }
    else
    {
        if (!(image.save(filename))) //保存图像
        {
            QMessageBox::information(this,
                tr("Failed to save the image"),
                tr("Failed to save the image!"));
            return;
        }
    }
}

Chart::~Chart()
{
    delete chart;
}
