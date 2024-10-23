#include "mapwidget.h"

#include "simplemessagebox/simplemessagebox.h"
#include "commonhelper.h"

#include <QSslConfiguration>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPixmap>
#include <QSerialPortInfo>
#include <cstdlib>
#include <iostream>

MapWidget::MapWidget(QWidget *parent) : QDialog(parent)
{
    initUi();
    initCtrl();
    setModal(true);
}

MapWidget::~MapWidget()
{
    if (m_port.isOpen())
        m_port.close();
}

void MapWidget::initUi()
{
    auto pMovie = new QMovie(this);
    pMovie->setFileName(":/misc/mapwidget/images/loading.gif");
    pMovie->start();

    m_logoLabel.setObjectName("logoLabel");
    m_logoLabel.setText(QString("当前展示定位坐标：[") +m_location + "]");

    m_iconLabel.setMovie(pMovie);
    m_iconLabel.setAlignment(Qt::AlignCenter);
    m_logoLabel.setAlignment(Qt::AlignRight);

    auto *pLayout = new QGridLayout;
    pLayout->setColumnStretch(0, 1);
    pLayout->addWidget(m_zoomInButton, 0, 1);
    pLayout->addWidget(m_zoomOutButton, 1, 1);

    auto *pVLayout = new QVBoxLayout;
    pVLayout->addStretch();
    pVLayout->addLayout(pLayout);
    pVLayout->addWidget(&m_logoLabel);
    m_iconLabel.setLayout(pVLayout);

    auto *pMainLayout = new QVBoxLayout;
    pMainLayout->addWidget(&m_iconLabel);
    pMainLayout->setMargin(0);
    setLayout(pMainLayout);
    setObjectName("map_widget");
    CommonHelper::setStyleSheet(":/misc/mapwidget/style/default.qss", this);

    installEventFilter(this);
    connect(m_zoomInButton, &QPushButton::clicked, this, [=](){
        int z = this->zoom.toInt();
        if (++z <= 18) {
            this->zoom = QString("%1").arg(z);
            this->requestMapImage(m_location);
        }
    });
    connect(m_zoomOutButton, &QPushButton::clicked, this, [=](){
        int z = this->zoom.toInt();
        if (--z >= 3) {
            this->zoom = QString("%1").arg(z);
            this->requestMapImage(m_location);
        }
    });
}

void MapWidget::initCtrl()
{
//    initSerialPort();
    requestMapImage(m_location);
}

//事件过滤器
QPoint point,last_point;//按下坐标
bool pres_flag,rele_flag;//按下松开标志
bool MapWidget::eventFilter(QObject *watched, QEvent *event)
{

    if(watched == this ){
        switch (event->type()) {
        case QEvent::MouseButtonPress://鼠标按下事件
            pres_flag = 1;
            last_point.setY(cursor().pos().y());     // 记录按下点的y坐标
            last_point.setX(cursor().pos().x());     // 记录按下点的x坐标
            break;

        case QEvent::MouseButtonRelease://鼠标松开事件
            rele_flag = 1;
            point.setY(cursor().pos().y());     // 记录按下点的y坐标
            point.setX(cursor().pos().x());     // 记录按下点的x坐标
//            m_logoLabel.setText(QString("鼠标松开位置：") + QString::number(point.x()) + QString("，") + QString::number(point.y()));
            break;
        }
    }

    if(pres_flag==1 && rele_flag==1)
    {
        pres_flag = 0;
        rele_flag = 0;
        int m_x, m_y, dis;
        m_x = point.x()-last_point.x();
        m_y = point.y()-last_point.y();
        dis = m_x * m_x + m_y * m_y;
        if(dis > 8100)
        {
            QString m_zoom = zoom;
            //计算需要偏移多少东经北纬
            double move_x = m_x*0.00000038*(19-m_zoom.toInt())*(19-m_zoom.toInt())*(19-m_zoom.toInt())*(19-m_zoom.toInt());
            double move_y = m_y*0.00000033*(19-m_zoom.toInt())*(19-m_zoom.toInt())*(19-m_zoom.toInt())*(19-m_zoom.toInt());
            m_location_x -= move_x;
            m_location_y += move_y;
            m_location = QString("%1,%2").arg(m_location_x).arg(m_location_y);
//            m_logoLabel.setText(QString("当前展示定位坐标：[") +m_location + "]");
            requestMapImage(m_location);
        }

    }

    return QWidget::eventFilter(watched,event);//将事件传递给父类
}


void MapWidget::initSerialPort()
{
    m_port.setPortName("ttymxc5");

    if(!m_port.open(QIODevice::ReadWrite)) {
        SimpleMessageBox::infomationMessageBox("未检测到设备，请重试");
        m_logoLabel.setText(QString("未检测到GPS设备，当前展示定位坐标：[") +m_location + "]");
        return;
    }

    m_port.setBaudRate(QSerialPort::Baud9600, QSerialPort::AllDirections);
    m_port.setDataBits(QSerialPort::Data8);
    m_port.setFlowControl(QSerialPort::NoFlowControl);
    m_port.setParity(QSerialPort::NoParity);
    m_port.setStopBits(QSerialPort::OneStop);

    connect(&m_port, &QSerialPort::readyRead, this, &MapWidget::portReadReady);
}

void MapWidget::requestMapImage(const QString &center)
{
    QString url = baidudUrl.arg(baidudAk).arg(center).arg(zoom);

    m_array.clear();
    requestNetwork(url);
}

void MapWidget::requestNetwork(const QString &url)
{
    QSslConfiguration config;
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1_0);

    QNetworkRequest networkRequest;
    networkRequest.setSslConfiguration(config);
    networkRequest.setUrl(url);

    QNetworkReply *newReply = m_networkAccessManager.get(networkRequest);

    connect(newReply, &QNetworkReply::readyRead, this, &MapWidget::netReadyRead);
    connect(newReply, &QNetworkReply::finished, newReply, &QNetworkReply::deleteLater);
}

void MapWidget::netReadyRead()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    m_array.append(reply->readAll());

    QPixmap pixmap(m_array);

    if(pixmap.loadFromData(m_array)) {
        m_iconLabel.setPixmap(pixmap);
    }
}

void MapWidget::portReadReady()
{
    while (m_port.bytesAvailable()) {
        QString line = m_port.readLine();
        auto location = parseGpsData(line);
        if (!location.isEmpty()) {
            m_location = location;
            line = "定位成功，[" + location + "]";
            requestMapImage(location);
        }
        else {
            line = ("定位中... 请尝试移到空旷位置，展示坐标 [" + m_location + "]");
        }

        m_logoLabel.setText(line);
    }
}

QString MapWidget::parseGpsData(const QString &data)
{
    QString ret;

    if (data.contains(",,,,,"))
        return ret;

    auto list = data.trimmed().split(',');
    if (list.count() != 15)
        return ret;

    if (!list.at(0).contains("$GPGGA"))
        return ret;

    bool ok;
    auto e = list.at(4).toDouble(&ok);
    if (!ok)
        return ret;

    auto n = list.at(2).toDouble(&ok);
    if (!ok)
        return ret;

    int i = e / 100;
    double j = (e / 100  - i) * 100 / 60.0;
    ret = QString::number(i+j, 'f', 6);

    i = n / 100;
    j = (n / 100  - i) * 100 / 60.0;

    ret = ret + ',' + QString::number(i+j, 'f', 6);

    return ret;
}
