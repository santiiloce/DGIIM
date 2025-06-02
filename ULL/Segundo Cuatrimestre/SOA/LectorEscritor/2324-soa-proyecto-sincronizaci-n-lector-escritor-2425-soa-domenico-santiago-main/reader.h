#ifndef READER_H
#define READER_H

#include <QThread>
#include "buffer.h"

class Reader : public QThread {
    Q_OBJECT

public:
    Reader(Buffer *buf, int count, int id) : buffer(buf), readCount(count), readerId(id) {}

protected:
    void run() override;

private:
    Buffer *buffer;
    int readCount;
    int readerId; // ID único para el lector
};

#endif // READER_H
