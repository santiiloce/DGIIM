#ifndef BUFFER_H
#define BUFFER_H

#include <QMutex>
#include <QWaitCondition>

class Buffer {
public:
    Buffer(int maxSize);
    void add(int num);
    int remove();

private:
    int maxSize;
    int *queue; // Array que almacena los elementos
    int front, rear; // Punteros que vamos a usar para el Front y el Rear
    bool isEmpty();
    bool isFull();
    QMutex mutex;
    QWaitCondition notEmpty;
    QWaitCondition notFull;
};

#endif // BUFFER_H
