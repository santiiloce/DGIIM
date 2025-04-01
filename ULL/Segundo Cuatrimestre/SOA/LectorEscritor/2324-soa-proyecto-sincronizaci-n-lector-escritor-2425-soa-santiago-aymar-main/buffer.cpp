#include "buffer.h"
#include <QDebug>

Buffer::Buffer(int maxSize, int totalReaders, int read_writeCount) : maxSize(maxSize), totalReaders(totalReaders),front(0),
    rear(0), activeReaders(0), waitingWriters(0), activeWriters(0), itemsAvailable(0), readersReadCurrent(0),
    maxWrites(read_writeCount), totalWrites(0){

    queue = new int[maxSize];  // Inicializa el buffer
}


std::pair<int, int> Buffer::read(int readerId) { // Asume que ahora pasas un ID de lector a read
    QMutexLocker locker(&mutex);
    // Los lectores deben esperar si no hay elementos disponibles para leer,
    // o si hay escritores activos, o si este lector ya ha leído el elemento actual
    while (itemsAvailable == 0 || activeWriters > 0 || readersWhoReadCurrent.find(readerId) != readersWhoReadCurrent.end()) {
        canRead.wait(&mutex);
    }
    ++activeReaders;
    // Leer el número de la posición actual 'front'
    int num = queue[front];
    int readPosition = front;

    // Registrar que este lector ha leído el elemento actual
    readersWhoReadCurrent.insert(readerId);
    readersReadCurrent++;

    if (readersReadCurrent == totalReaders) {
        // Todos los lectores han leído el elemento actual, avanzar 'front'
        front = (front + 1) % maxSize;
        // Limpiar el conjunto de lectores para el próximo elemento
        readersWhoReadCurrent.clear();
        readersReadCurrent = 0;

        --itemsAvailable; // Disminuye los ítems disponibles tras todos los lectores haber leído.
        canWrite.wakeOne(); // Permite a los escritores escribir si están esperando.
    }

    --activeReaders;
    if (activeReaders == 0) {
        canRead.wakeAll(); // Despierta a los lectores restantes si aún no han leído el elemento actual.
    }
    return {num, readPosition};
}


int Buffer::write(int num) {
    QMutexLocker locker(&mutex);
    // Los escritores deben esperar si hay lectores activos, o si hay otros escritores activos,
    // o si el buffer está lleno (itemsAvailable == maxSize)
    while (activeReaders > 0 || activeWriters > 0 || itemsAvailable == maxSize) {
        qDebug("--------PAUSA DE ESCRITURA---------");
        ++waitingWriters;
        canWrite.wait(&mutex);
        --waitingWriters;
    }

    // Verificar si se ha alcanzado el límite total de escrituras
    if (totalWrites >= maxWrites) {
        return -1; // Indicar que se ha alcanzado el límite de escrituras
    }

    ++activeWriters;

    // Escribir el número en la posición actual 'rear'
    queue[rear] = num;
    int writePosition = rear;
    rear = (rear + 1) % maxSize; // Avanzar 'rear' circularmente
    ++itemsAvailable; // Incrementar elementos disponibles
    ++totalWrites; // Incrementar el contador de escrituras totales

    --activeWriters;
    if (waitingWriters > 0) {
        canWrite.wakeOne();
    } else {
        canRead.wakeAll(); // Notifica a los lectores que hay nuevos elementos disponibles
    }
    return writePosition;
}
