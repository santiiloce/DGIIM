#include "writer.h"
#include <QDebug>
#include <QRandomGenerator>
#include <QThread>

void Writer::run() {
    for (int i = 0; i < writeCount; ++i) {
        int num = QRandomGenerator::global()->bounded(100);
        int rear;

        // TODO: Escribe en el buffer

        // Comprobar si se alcanzó el límite máximo de escrituras permitidas.
        if (rear == -1) {
            qDebug() << "Límite de escrituras alcanzado. Escritor" << writerId << "termina prematuramente.";
            break; // Salir del bucle for.
        }

        qDebug() <<  i << "Writer(" << QThread::currentThreadId() << ") ID:" << writerId << "Writing from pos:" << rear << ", Value:" << num;
        QThread::msleep(QRandomGenerator::global()->bounded(500)); // Simulate time to produce item
    }
    qDebug() << "-----Se terminó de escribir writing " << writerId << "-----";

}
