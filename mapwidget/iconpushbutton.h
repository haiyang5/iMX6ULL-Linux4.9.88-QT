#ifndef ICONPUSHBUTTON_H
#define ICONPUSHBUTTON_H
#include<QPushButton>
#include<QPropertyAnimation>
#include<QString>
#include<QEvent>
#include<QMouseEvent>

#include <QObject>
#include <QWidget>

class iconPushButton : public QPushButton
{
    Q_OBJECT
public:
    iconPushButton(QString normal_path,QString press_path="",int pixwidth=70,int pixheight=70);
    void zoom1();
    void zoom2();
private:
    QString normal_path;
    QString press_path;
    QPropertyAnimation* animation;
protected:
    void mousePressEvent(QMouseEvent * e);
    void mouseReleaseEvent(QMouseEvent * e);
signals:

public slots:
};

#endif // ICONPUSHBUTTON_H
