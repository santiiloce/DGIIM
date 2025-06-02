#include "consumer.h"
#include <QRandomGenerator>
#include <QDebug>

Consumer::Consumer(Buffer *buffer, int consumeCount) : buffer(buffer), consumeCount(consumeCount) {}

void Consumer::run() {
    int num;
    for (int i = 0; i < consumeCount; ++i) {

        // TODO: Borra elemento y almacena el valor en la variable num
        num = buffer->remove();
        qDebug() << i << " Consumido:" << num;
        msleep(QRandomGenerator::global()->bounded(250)); // Simulate time to process item
    }
    qDebug("-----Se terminó de consumir-----");
}
