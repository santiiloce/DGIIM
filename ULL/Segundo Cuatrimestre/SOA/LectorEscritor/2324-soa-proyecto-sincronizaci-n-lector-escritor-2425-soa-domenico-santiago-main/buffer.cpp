#include "buffer.h"
#include <QDebug>

Buffer::Buffer(int maxSize, int totalReaders, int read_writeCount) : maxSize(maxSize), totalReaders(totalReaders),front(0),
    rear(0), activeReaders(0), waitingWriters(0), activeWriters(0), itemsAvailable(0), readersReadCurrent(0),
    maxWrites(read_writeCount), totalWrites(0){

    queue = new int[maxSize];  // Inicializa el buffer
}

std::pair<int, int> Buffer::read(int readerId) { // Asume que ahora pasas un ID de lector a read
    QMutexLocker locker(&mutex);
    // TODO: Completar la condición para que los lectores esperen adecuadamente.
    while (itemsAvailable == 0 || readersWhoReadCurrent.count(readerId)) {
        canRead.wait(&mutex);
    }
    ++activeReaders;
    // TODO: Implementar la lógica para leer del buffer.
    int num = queue[front]/* COMPLETAR: obtener el número del buffer */;
    int readPosition = front/* COMPLETAR: obtener la posición actual de 'front' */;

    // TODO: Actualizar el estado para reflejar que este lector ha leído el elemento.
    // HINT: Puede necesitar actualizar 'readersWhoReadCurrent' y 'readersReadCurrent'.
    readersWhoReadCurrent.insert(readerId);
    ++readersReadCurrent;
    if (readersReadCurrent == totalReaders/* COMPLETAR: Todos los lectores han leído el elemento.*/) {

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
    // TODO: Completar las condiciones para que los escritores esperen adecuadamente.
    while (itemsAvailable == maxSize || activeWriters > 0/* COMPLETAR: condiciones bajo las cuales el escritor debe esperar */) {
        ++waitingWriters;
        qDebug("--------PAUSA DE ESCRITURA---------");
        canWrite.wait(&mutex);
        --waitingWriters;
    }

    // TODO: Verificar si se ha alcanzado el límite total de escrituras y actuar en consecuencia.
    if (totalWrites >= maxWrites) {
        // HINT: Debe retornar un valor especial si no se permite más escritura. Por ejemplo -1.
        return -1;
    }

    ++activeWriters;

    // TODO: Implementar la lógica para escribir en el buffer y actualiza el estado de las variables.
    queue[rear] = num;
    int writePosition = rear/* COMPLETAR: calcular la nueva posición de 'rear' y escribir en el buffer */;
        // HINT: Deberás actualizar el estado del rear, itemsAvailable y totalWrites.
        // Además de escribir en el buffer

    rear = (rear + 1) % maxSize;
    ++itemsAvailable;
    ++totalWrites;
    --activeWriters;

    if (waitingWriters > 0) {
        canWrite.wakeOne();
    } else {
        canRead.wakeAll(); // Notifica a los lectores que hay nuevos elementos disponibles
    }
    return writePosition;
}
