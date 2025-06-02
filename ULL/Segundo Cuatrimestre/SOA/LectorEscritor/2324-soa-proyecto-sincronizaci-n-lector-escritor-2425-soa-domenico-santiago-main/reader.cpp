#include "reader.h"
#include <QDebug>
#include <QRandomGenerator>
#include <QThread>

void Reader::run() {
    for (int i = 0; i < readCount; ++i) {
        // TODO: Lee un elemento y obten un pair con el elemento leido y la posición del front

        qDebug() << i << "Reader(" << QThread::currentThreadId() << ") ID:" << readerId << "Reading from pos:" << front << ", Value:" << num;
        QThread::msleep(QRandomGenerator::global()->bounded(250)); // Simulate time to process item
    }
    qDebug() << "-----Se terminó de leer reader " << readerId << "-----";
}
