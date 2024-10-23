#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QDialog>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QMovie>
#include <QSerialPort>
#include <QByteArray>
#include <QPushButton>
#include "iconpushbutton.h"

class MapWidget : public QDialog
{
    Q_OBJECT

    const QString baidudAk  = "6bsI90pRFA4jcxUMsQ84A2EWyLVgaNcu";
    QString zoom = "16";
    const QString baidudUrl = "https://api.map.baidu.com/staticimage/v2?ak=%1&mcode=666666&center=%2&width=1024&height=600&zoom=%3&scale=1&markers=%2&markerStyles=m,Y,0x00FF00";

public:
    explicit MapWidget(QWidget *parent = nullptr);
    ~MapWidget();

private:
    void initUi();
    void initCtrl();
    void initSerialPort();
    void requestMapImage(const QString &center);
    void requestNetwork(const QString &url);
    QString parseGpsData(const QString &data);

    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void netReadyRead();
    void portReadReady();

private:
    QLabel m_iconLabel;
    QLabel m_logoLabel;
    iconPushButton* m_zoomInButton = new iconPushButton(":/misc/mapwidget/images/zoom_in.png");
    iconPushButton* m_zoomOutButton = new iconPushButton(":/misc/mapwidget/images/zoom_out.png");

    QByteArray m_array;
    QNetworkAccessManager m_networkAccessManager;
    //QString m_location = QString("118.804341,31.975024");,
    double m_location_x = 106.707372;
    double m_location_y = 29.520451;
    QString m_location = QString("%1,%2").arg(m_location_x).arg(m_location_y);

    QSerialPort m_port;
};

#endif // MAPWIDGET_H
