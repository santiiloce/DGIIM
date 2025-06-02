#ifndef CONSUMER_H
#define CONSUMER_H

#include <QThread>
#include "buffer.h"

class Consumer : public QThread {
    Q_OBJECT
public:
    Consumer(Buffer *buffer, int consumeCount);
    void run() override;

private:
    Buffer *buffer;
    int consumeCount;
};

#endif // CONSUMER_H
