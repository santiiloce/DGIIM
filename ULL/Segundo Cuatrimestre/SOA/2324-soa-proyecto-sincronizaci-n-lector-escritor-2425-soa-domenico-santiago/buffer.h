#ifndef BUFFER_H
#define BUFFER_H

#include <QMutex>
#include <QWaitCondition>
#include <utility> // Para std::pair
#include <set> // Para std::set

class Buffer {
public:
    Buffer(int maxSize, int totalReaders, int read_writeCount); // Añadimos totalReaders para conocer el número total de lectores
    std::pair<int, int> read(int readerId);
    int write(int num); // Cambio: write va a retornar el rear para el log

private:
    int *queue; // Array que almacena los elementos del buffer
    std::set<int> readersWhoReadCurrent; // Conjunto para llevar registro de los lectores que han leído el elemento actual
    int maxSize; // Tamaño máximo del buffer
    int itemsAvailable; // Para controlar los items leídos
    int front, rear; // Punteros que vamos a usar para el frente y el final del buffer
    int activeReaders; // Contador de lectores activos
    int waitingWriters; // Contador de escritores esperando
    int activeWriters; // Contador de escritores activos (generalmente será 0 o 1)
    int totalReaders; // Número total de lectores
    int readersReadCurrent; // Cuántos lectores han leído el valor actual de 'front'
    int maxWrites; // Límite total de elementos que se pueden escribir
    int totalWrites; //Número de writes hechos
    QMutex mutex; // Mutex para proteger el acceso al buffer
    QWaitCondition canRead, canWrite; // Condiciones para controlar la lectura y escritura
};


#endif // BUFFER_H
