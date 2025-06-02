#include "producer.h"
#include <QRandomGenerator>
#include <QDebug>

Producer::Producer(Buffer *buffer, int produceCount) : buffer(buffer), produceCount(produceCount) {}

void Producer::run() {
    int num;
    for (int i = 0; i < produceCount; ++i) {
        num = QRandomGenerator::global()->bounded(100);

        // TODO: Añade num al buffer
        buffer->add(num);
        qDebug() << i << " Producido:" << num;
        msleep(QRandomGenerator::global()->bounded(200)); // Simulate time to produce item
    }
    qDebug("-----Se terminó de producir-----");
}
