#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(1620,1080);
    port = new QComboBox();
    port->addItem(tr("端口号"));
    port->addItem(tr("COM1"));
    port->addItem(tr("COM2"));
    port->addItem(tr("COM3"));
    port->addItem(tr("COM4"));
    port->addItem(tr("COM5"));
    baud = new QComboBox();
    baud->addItem(tr("波特率"));
    baud->addItem(tr("1200"));
    baud->addItem(tr("2400"));
    baud->addItem(tr("4800"));
    baud->addItem(tr("9600"));
    baud->addItem(tr("19200"));
    baud->addItem(tr("38400"));
    baud->addItem(tr("57600"));
    baud->addItem(tr("115200"));
    start = new QPushButton(tr("开始采集"));
    end = new QPushButton(tr("结束采集"));
    QHBoxLayout *top_lay = new QHBoxLayout();//上方布局
    top_lay->addWidget(port,0);
    top_lay->setStretchFactor(port,1);
    top_lay->addWidget(baud,1);
    top_lay->setStretchFactor(baud,1);
    top_lay->addWidget(start,2);
    top_lay->setStretchFactor(start,1);
    top_lay->addWidget(end,3);
    top_lay->setStretchFactor(end,1);
    top_lay->setMargin(10);
    top_lay->setSpacing(5);
    chart = new Chart();
    chart->init_chart("无线模块调试",-100,100);
    QVBoxLayout *main_lay = new QVBoxLayout(this);
    main_lay->addLayout(top_lay,0);
    main_lay->setStretchFactor(top_lay,1);
    main_lay->addWidget(chart,1);
    main_lay->setStretchFactor(main_lay,10);
    main_lay->setMargin(10);
    main_lay->setSpacing(5);
    global_port.setParity(QSerialPort::NoParity);//校验位
    global_port.setDataBits(QSerialPort::Data8);//数据位
    global_port.setStopBits(QSerialPort::OneStop);//停止位
    global_port.setFlowControl(QSerialPort::NoFlowControl);//流控制一般没用
//    global_port.setPortName("COM4");
//    global_port.setBaudRate(QSerialPort::Baud2400);
    connect(start,SIGNAL(clicked()),this,SLOT(start_collect()));
    connect(end,SIGNAL(clicked()),this,SLOT(end_collect()));
    connect(port,static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&Widget::port_handle);
    connect(baud,static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&Widget::baud_handle);
    connect(&global_port ,SIGNAL(readyRead()) , this ,SLOT(on_readyRead()));
}
void Widget::port_handle(int index)//端口号槽函数
{
    switch(port->currentIndex())
    {
    case 1:
    global_port.setPortName("COM1");
        break;
    case 2:
    global_port.setPortName("COM2");
        break;
    case 3:
    global_port.setPortName("COM3");
        break;
    case 4:
    global_port.setPortName("COM4");
        break;
    case 5:
    global_port.setPortName("COM5");
        break;
    }
}
void Widget::baud_handle(int index)//波特率槽函数
{
    switch(baud->currentIndex())
    {
    case 1:
    global_port.setBaudRate(QSerialPort::Baud1200);
        break;
    case 2:
    global_port.setBaudRate(QSerialPort::Baud2400);
        break;
    case 3:
    global_port.setBaudRate(QSerialPort::Baud4800);
        break;
    case 4:
    global_port.setBaudRate(QSerialPort::Baud9600);
        break;
    case 5:
    global_port.setBaudRate(QSerialPort::Baud19200);
        break;
    case 6:
    global_port.setBaudRate(QSerialPort::Baud38400);
        break;
    case 7:
    global_port.setBaudRate(QSerialPort::Baud57600 );
        break;
    case 8:
    global_port.setBaudRate(QSerialPort::Baud115200);
        break;
    }
}
void Widget::start_collect()
{
    qDebug() << global_port.portName() << global_port.baudRate();
    global_port.open(QSerialPort::ReadWrite);
}
void Widget::on_readyRead()
{
    buff = global_port.readAll();
    double number = (buff[0]-'0')*10 + (buff[1]-'0');
    qDebug() << number;
    chart->draw_line(QDateTime::currentDateTime(),number);
}
void Widget::end_collect()
{
    global_port.close();
}
Widget::~Widget()
{
    delete this;
}
