#include "producer.h"
#include <QRandomGenerator>
#include <QDebug>

Producer::Producer(Buffer *buffer, int produceCount) : buffer(buffer), produceCount(produceCount) {}

void Producer::run() {
    int num;
    int position;
    for (int i = 0; i < produceCount; ++i) {
        num = QRandomGenerator::global()->bounded(100);
        
        // Añadir num al buffer y obtener la posición donde se escribió
        position = buffer->write(num);
        
        // Verificar si hemos alcanzado el límite de escrituras
        if (position == -1) {
            qDebug() << "Límite de escrituras alcanzado. Terminando producción.";
            break;
        }
        
        qDebug() << "Escritor - Item producido:" << num << "en la posición:" << position;
        msleep(QRandomGenerator::global()->bounded(200)); // Simular tiempo para producir item
    }
    qDebug("-----Se terminó de producir-----");
}
