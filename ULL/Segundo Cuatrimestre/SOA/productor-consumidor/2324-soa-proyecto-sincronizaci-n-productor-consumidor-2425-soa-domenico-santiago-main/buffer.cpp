#include "buffer.h"

Buffer::Buffer(int maxSize) : maxSize(maxSize), front(0), rear(0) {
    queue = new int[maxSize];
}

bool Buffer::isEmpty(){
    return front == rear;
}

bool Buffer::isFull(){
    return ((rear + 1) % maxSize == front);
}

void Buffer::add(int num) {
    QMutexLocker locker(&mutex);
    // TODO: Completar la condición para verificar si el buffer está lleno.
    while (isFull()) {
        notFull.wait(&mutex); // Espera hasta que haya espacio
    }
    // TODO: Añadir el número al buffer.
    // HINT: Necesitas actualizar la posición 'rear'.
    queue[rear] = num;
    rear = (rear + 1) % maxSize;
    notEmpty.wakeOne();
    // TODO: Notificar a los consumidores que hay un nuevo elemento disponible.
    // HINT: Despierta la variable que registra el que no está vacío.
}

int Buffer::remove() {
    QMutexLocker locker(&mutex);
    // TODO: Completar la condición para verificar si el buffer está vacío.
    isEmpty();
    while (isEmpty()) {
        notEmpty.wait(&mutex); // Espera hasta que haya algo para consumir
    }
    // TODO: Remover un número del buffer.
    // HINT: Necesitas actualizar la posición 'front'.
    int num = queue[front];
    front = (front + 1) % maxSize;
    // TODO: Notificar a los productores que hay espacio disponible.
    // HINT: Despierta la variable que registra el que no está lleno.
    notFull.wakeOne();
    // TODO: Devolver el número removido.
    return num;
}

