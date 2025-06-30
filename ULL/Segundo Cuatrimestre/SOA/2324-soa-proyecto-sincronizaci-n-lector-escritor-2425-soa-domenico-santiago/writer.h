#ifndef WRITER_H
#define WRITER_H

#include <QThread>
#include "buffer.h"

class Writer : public QThread {
    Q_OBJECT

public:
    Writer(Buffer *buf, int count, int id) : buffer(buf), writeCount(count), writerId(id)  {}

protected:
    void run() override;

private:
    Buffer *buffer;
    int writeCount;
    int writerId;
};

#endif // WRITER_H
