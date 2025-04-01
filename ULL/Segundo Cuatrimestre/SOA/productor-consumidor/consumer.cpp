#include "consumer.h"
#include <QRandomGenerator>
#include <QDebug>

Consumer::Consumer(Buffer *buffer, int consumeCount) : buffer(buffer), consumeCount(consumeCount) {}

void Consumer::run() {
    int num;
    int position;
    for (int i = 0; i < consumeCount; ++i) {
        // Consumir (leer) un elemento del buffer y almacenar el valor y su posición
        std::pair<int, int> result = buffer->read(i % consumeCount); // Usar i % consumeCount como ID de lector
        num = result.first;      // El número leído
        position = result.second; // La posición donde se leyó

        qDebug() << "Lector" << i % consumeCount << "- Item leído:" << num << "desde la posición:" << position;
        msleep(QRandomGenerator::global()->bounded(250)); // Simular tiempo para procesar el item
    }
    qDebug("-----Se terminó de consumir-----");
}
