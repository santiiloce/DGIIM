#include <QCoreApplication>
#include <QThread>
#include <QDebug>
#include <QElapsedTimer>
#include <unistd.h>
#include <atomic>

#define WORK 1000000
std::atomic_int iterator=0;
//int iterator=0;
const std::string adn="ACGT";

class Thread: public QThread
{
private:
    void run() override
    {
        while(iterator < WORK)
        {
            //usleep(10);
            //qDebug() << adn[iterator%4];
            iterator++;
        }
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Thread t1,t2;
    QElapsedTimer timer1;

    qDebug() << "start";
    timer1.start();
    t1.start();
    t2.start();

    t1.wait();
    t2.wait();
    qDebug() << timer1.nsecsElapsed();
    qDebug() << "end";

    return a.exec();
}

