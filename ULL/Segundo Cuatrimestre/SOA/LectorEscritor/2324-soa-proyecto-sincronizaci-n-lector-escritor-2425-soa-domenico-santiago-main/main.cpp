#include <QCoreApplication>
#include "writer.h"
#include "reader.h"
#include "buffer.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    const int bufferSize = 10;
    const int read_writeCount = 50;  // Número de veces que cada lector debe leer, y que el escritor/escritores va a poder escribir
    const int totalReaders = 3; //Número total de lectores

    Buffer buffer(bufferSize, totalReaders, read_writeCount);

    Writer writer1(&buffer, read_writeCount, 1);
    Writer writer2(&buffer, read_writeCount, 2);
    Reader reader1(&buffer, read_writeCount, 1); // Segundo lector con ID 1
    Reader reader2(&buffer, read_writeCount, 2); // Segundo lector con ID 2
    Reader reader3(&buffer, read_writeCount, 3); // Segundo lector con ID 3

    writer1.start();
    writer2.start();
    reader1.start();
    reader2.start(); // Inicia el segundo lector
    reader3.start(); // Inicia el segundo lector

    writer1.wait();
    writer2.wait();
    reader1.wait();
    reader2.wait(); // Espera a que el segundo lector termine
    reader3.wait(); // Espera a que el segundo lector termine


    return a.exec();
}
