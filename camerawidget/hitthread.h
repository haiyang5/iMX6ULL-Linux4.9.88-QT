#ifndef HITTHREAD_H
#define HITTHREAD_H

#include <QObject>
#include <QThread>

class HitThread : public QObject
{
    Q_OBJECT
public:
    explicit HitThread();
    ~HitThread();
    int check = 0;

public slots:
    bool start();
    void quit();
    void wait();

private slots:
    void tmain();

signals:
    void readReady(int value);
    void finished();

private:
    QString m_path;
    QThread m_thread;
    int m_fd = -1;
};

#endif // HITTHREAD_H
