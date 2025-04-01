#include "buffer.h"

Buffer::Buffer(int maxSize) : maxSize(maxSize), front(0), rear(0) {
    queue = new int[maxSize];
}

void Buffer::add(int num) {
    QMutexLocker locker(&mutex);
    // TODO: Completar la condición para verificar si el buffer está lleno.
    while (/* COMPLETAR: condición para cuando el buffer esté lleno */) {
        notFull.wait(&mutex); // Espera hasta que haya espacio
    }
    // TODO: Añadir el número al buffer.
    // HINT: Necesitas actualizar la posición 'rear'.

    // TODO: Notificar a los consumidores que hay un nuevo elemento disponible.
    // HINT: Despierta la variable que registra el que no está vacío.
}

int Buffer::remove() {
    QMutexLocker locker(&mutex);
    // TODO: Completar la condición para verificar si el buffer está vacío.
    while (/* COMPLETAR: condición para cuando el buffer esté vacío */) {
        notEmpty.wait(&mutex); // Espera hasta que haya algo para consumir
    }
    // TODO: Remover un número del buffer.
    // HINT: Necesitas actualizar la posición 'front'.

    // TODO: Notificar a los productores que hay espacio disponible.
    // HINT: Despierta la variable que registra el que no está lleno.

    // TODO: Devolver el número removido.
}

