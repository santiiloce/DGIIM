#include "buffer.h"
#include <QDebug>

Buffer::Buffer(int maxSize, int totalReaders, int read_writeCount) : maxSize(maxSize), totalReaders(totalReaders),front(0),
    rear(0), activeReaders(0), waitingWriters(0), activeWriters(0), itemsAvailable(0), readersReadCurrent(0),
    maxWrites(read_writeCount), totalWrites(0){

    queue = new int[maxSize];  // Inicializa el buffer
}


std::pair<int, int> Buffer::read(int readerId) { // Asume que ahora pasas un ID de lector a read
    QMutexLocker locker(&mutex);
    while (itemsAvailable == 0 || activeWriters != 0 || readersWhoReadCurrent.count(readerId) > 0) {
        canRead.wait(&mutex);
    }
    ++activeReaders;                // incremento de los lectores activos
    int num = queue[front];         // obtener el número del buffer
    int readPosition = front;       // obtener la posición actual de 'front'

    // TODO: Actualizar el estado para reflejar que este lector ha leído el elemento.
    // HINT: Puede necesitar actualizar 'readersWhoReadCurrent' y 'readersReadCurrent'.
    readersWhoReadCurrent.insert(readerId);
    readersReadCurrent += 1;
    if (totalReaders == readersReadCurrent) {// Todos los lectores han leído el elemento

        // TODO: Actualizar el estado de las variables una vez se han leído todos los elementos
        // HINT: Puede necesitar actualizar el 'front', 'readersWhoReadCurrent' y 'readersReadCurrent'.
        front = (front + 1) % maxSize;
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

    while (activeReaders != 0 || activeWriters != 0 || rear+1 == front) {
        qDebug("--------PAUSA DE ESCRITURA---------");
        canWrite.wait(&mutex);
    }

    if (maxWrites == totalWrites) { //Verificar si se ha alcanzado el límite total de escrituras.
        return -1;  //Si es así, devuelve -1.
    }

    ++activeWriters;


    int writePosition = rear;

    itemsAvailable = itemsAvailable+1;  //Actualizar itemsAvailable
    totalWrites = totalWrites+1;    //Actualizamos totalWrites
    if (rear == maxSize - 1) {  //Necesitas actualizar la posición 'rear'.
        rear = 0;
    } else {
        rear += 1;
    }

    queue[writePosition] = num; //Escribimos en el buffer


    --activeWriters;
    if (waitingWriters > 0) {
        canWrite.wakeOne();
    } else {
        canRead.wakeAll(); // Notifica a los lectores que hay nuevos elementos disponibles
    }
    return writePosition;
}
