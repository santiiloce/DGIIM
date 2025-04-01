#ifndef PRODUCER_H
#define PRODUCER_H

#include <QThread>
#include "buffer.h"

class Producer : public QThread {
    Q_OBJECT
public:
    Producer(Buffer *buffer, int produceCount);
    void run() override;

private:
    Buffer *buffer;
    int produceCount;
};

#endif // PRODUCER_H
