#include "hitthread.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <QDebug>

HitThread::HitThread() : QObject(NULL)
{
    m_path = "/dev/adxl345";
    qDebug()<< "path:" << m_path;
    moveToThread(&m_thread);

    connect(&m_thread, &QThread::started, this, &HitThread::tmain);
    connect(&m_thread, &QThread::finished, this, &HitThread::finished);
}

HitThread::~HitThread()
{
}

bool HitThread::start()
{
    m_fd = ::open(m_path.toLatin1().data(), O_RDONLY);

    if (m_fd == -1) {
        qDebug()<< "HitThread::start(): open falid";
        return false;
    }

    qDebug()<< "HitThread::start(): m_fd=" << m_fd;
    m_thread.start();

    return true;
}

void HitThread::quit()
{
    m_thread.requestInterruption();
    m_thread.quit();
}

void HitThread::wait()
{
    m_thread.wait();
}

void HitThread::tmain()
{
    int value = 0;

    qDebug()<< "HitThread::tmain(): m_fd=" << m_fd;
    while (!QThread::currentThread()->isInterruptionRequested()) {
        if (!check) {
            if (::read(m_fd, &value, 4) == 0) {
                emit readReady(value);
                if (value == 1) {
                    check = 1;
                }
            }
            else {
                emit readReady(-1);
            }
        }
        m_thread.msleep(300);
    }

    ::close(m_fd);
}
