#include <QCoreApplication>
#include <QElapsedTimer>
#include <QDebug>
#include "writer.h"
#include "reader.h"
#include "buffer.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    const int bufferSize = 10;
    const int read_writeCount = 50;  // Número de veces que cada lector debe leer, y que el escritor/escritores va a poder escribir
    const int totalReaders = 3; //Número total de lectores
    QElapsedTimer timer;

    Buffer buffer(bufferSize, totalReaders, read_writeCount);

    Writer writer(&buffer, read_writeCount, 1);
    Reader reader1(&buffer, read_writeCount, 1, 3); //  Lector con ID 1
    Reader reader2(&buffer, read_writeCount, 2, 3); //  Lector con ID 2
    Reader reader3(&buffer, read_writeCount, 3, 3); //  Lector con ID 3


    timer.start();
    writer.start();
    reader1.start();
    reader2.start();
    reader3.start();



    writer.wait();
    reader1.wait();
    reader2.wait(); // Espera a que el segundo lector termine
    reader3.wait(); // Espera a que el segundo lector termine

    qint64 elapsedTime = timer.elapsed();
    qDebug() << "Tiempo transcurrido:" << elapsedTime << "milisegundos";

    qDebug("Fin de programa");
    return a.exec();
}
